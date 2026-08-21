"use strict";

const STUDY_PATH = "ALGORITHM_STUDY_ORDER.md";
const STORAGE = {
  completed: "boj-theory.completed.v1",
  visited: "boj-theory.visited.v1",
  theme: "boj-theory.theme.v1",
  codeWrap: "boj-theory.code-wrap.v1",
  lastRoute: "boj-theory.last-route.v1",
};

const state = {
  manifest: null,
  currentPath: null,
  currentAlgorithm: null,
  routeToken: 0,
  query: "",
  completed: loadSet(STORAGE.completed),
  visited: loadSet(STORAGE.visited),
  openPhases: new Set([1]),
  documentCache: new Map(),
  copyBlocks: [],
  codeWrap: localStorage.getItem(STORAGE.codeWrap) === "true",
  tocObserver: null,
  toastTimer: null,
  scrollFrame: null,
};

const elements = {};


document.addEventListener("DOMContentLoaded", boot);


async function boot() {
  cacheElements();
  applySavedTheme();
  bindEvents();
  if ("scrollRestoration" in history) history.scrollRestoration = "manual";

  if (location.protocol === "file:") {
    showError("이 파일은 직접 열 수 없습니다. theory 폴더의 start_theory_web.cmd를 실행해 주세요.");
    return;
  }

  try {
    state.manifest = await fetchJson("/api/manifest");
    if (!state.manifest?.algorithms?.length) {
      throw new Error("ALGORITHM_STUDY_ORDER.md에서 학습 항목을 찾지 못했습니다.");
    }

    renderSidebar();
    updateProgressUI();

    const initialPath = pathFromHash();
    history.replaceState(
      { app: true, index: 0, path: initialPath, scroll: 0, originPath: null },
      "",
      routeHash(initialPath),
    );
    await renderPath(initialPath, { restoreScroll: 0, focus: false });
  } catch (error) {
    showError(error.message || "학습 웹을 시작하지 못했습니다.");
  }
}


function cacheElements() {
  const ids = [
    "menu-button", "brand-button", "search-input", "top-progress-label",
    "theme-button", "sidebar", "progress-ring", "progress-circle", "progress-percent",
    "progress-count", "continue-button", "study-nav-button",
    "search-result-count", "phase-navigation", "sidebar-empty",
    "sidebar-backdrop", "back-button", "home-button", "breadcrumb",
    "complete-button", "reload-button", "loading-view", "error-view",
    "error-message", "error-home-button", "reader-layout", "document-view",
    "document-toc", "document-pagination", "previous-button", "next-button",
    "toast",
  ];
  for (const id of ids) elements[toCamel(id)] = document.getElementById(id);
}


function bindEvents() {
  elements.brandButton.addEventListener("click", () => navigateTo(STUDY_PATH));
  elements.studyNavButton.addEventListener("click", () => navigateTo(STUDY_PATH));
  elements.homeButton.addEventListener("click", () => navigateTo(STUDY_PATH));
  elements.errorHomeButton.addEventListener("click", () => navigateTo(STUDY_PATH));
  elements.backButton.addEventListener("click", goBack);
  elements.themeButton.addEventListener("click", toggleTheme);
  elements.menuButton.addEventListener("click", () => setSidebarOpen(!elements.sidebar.classList.contains("open")));
  elements.sidebarBackdrop.addEventListener("click", () => setSidebarOpen(false));
  elements.continueButton.addEventListener("click", continueStudy);
  elements.completeButton.addEventListener("click", toggleCurrentComplete);
  elements.reloadButton.addEventListener("click", reloadCurrentDocument);
  elements.previousButton.addEventListener("click", () => navigateAdjacent(-1));
  elements.nextButton.addEventListener("click", () => navigateAdjacent(1));

  elements.searchInput.addEventListener("input", (event) => {
    state.query = event.target.value.trim().toLocaleLowerCase("ko");
    renderSidebar();
  });

  elements.phaseNavigation.addEventListener("click", handleSidebarClick);
  elements.documentView.addEventListener("click", handleDocumentClick);
  elements.documentToc.addEventListener("click", (event) => {
    const link = event.target.closest("a[href^='#']");
    if (!link) return;
    event.preventDefault();
    document.getElementById(link.getAttribute("href").slice(1))?.scrollIntoView({ behavior: "smooth", block: "start" });
  });

  window.addEventListener("popstate", (event) => {
    const path = event.state?.path || pathFromHash();
    renderPath(path, { restoreScroll: event.state?.scroll || 0, focus: false });
  });

  window.addEventListener("scroll", rememberScrollPosition, { passive: true });
  window.addEventListener("keydown", handleKeyboard);
}


function handleKeyboard(event) {
  const activeTag = document.activeElement?.tagName;
  const typing = activeTag === "INPUT" || activeTag === "TEXTAREA";

  if ((event.ctrlKey || event.metaKey) && event.key.toLocaleLowerCase("en") === "k") {
    event.preventDefault();
    elements.searchInput.focus();
    elements.searchInput.select();
    return;
  }

  if (event.key === "Escape") {
    if (elements.sidebar.classList.contains("open")) setSidebarOpen(false);
    if (state.query) {
      state.query = "";
      elements.searchInput.value = "";
      renderSidebar();
    }
    return;
  }

  if (event.altKey && event.key === "ArrowLeft") {
    event.preventDefault();
    goBack();
    return;
  }

  if (!typing && !event.ctrlKey && !event.metaKey && !event.altKey) {
    if (event.key === "[") navigateAdjacent(-1);
    if (event.key === "]") navigateAdjacent(1);
    if (event.key === "/") {
      event.preventDefault();
      elements.searchInput.focus();
    }
  }
}


function handleSidebarClick(event) {
  const progressButton = event.target.closest("[data-progress-path]");
  if (progressButton) {
    event.stopPropagation();
    toggleProgress(progressButton.dataset.progressPath);
    return;
  }

  const phaseButton = event.target.closest("[data-phase-number]");
  if (phaseButton) {
    const number = Number.parseInt(phaseButton.dataset.phaseNumber, 10);
    if (state.openPhases.has(number)) state.openPhases.delete(number);
    else state.openPhases.add(number);
    renderSidebar();
    return;
  }

  const documentButton = event.target.closest("[data-document-path]");
  if (documentButton) navigateTo(documentButton.dataset.documentPath);
}


async function handleDocumentClick(event) {
  const documentLink = event.target.closest("[data-doc-path]");
  if (documentLink) {
    event.preventDefault();
    const originPath = state.currentAlgorithm?.path || history.state?.originPath || null;
    const returnPath = documentLink.dataset.returnPath || null;
    navigateTo(documentLink.dataset.docPath, { originPath, returnPath });
    return;
  }

  const copyButton = event.target.closest("[data-copy-index]");
  if (copyButton) {
    const value = state.copyBlocks[Number.parseInt(copyButton.dataset.copyIndex, 10)] || "";
    await copyText(value);
    showToast("코드를 복사했습니다.");
    return;
  }

  const taskButton = event.target.closest("[data-task-path]");
  if (taskButton) {
    toggleProgress(taskButton.dataset.taskPath);
    return;
  }

  const action = event.target.closest("[data-action]")?.dataset.action;
  if (action === "continue") continueStudy();
  if (action === "source-parent") {
    const parentPath = event.target.closest("[data-parent-path]")?.dataset.parentPath;
    if (parentPath) navigateTo(parentPath);
  }
  if (action === "problem-return") {
    const returnPath = event.target.closest("[data-return-path]")?.dataset.returnPath;
    if (returnPath) {
      if (history.state?.returnPath === returnPath && (Number(history.state?.index) || 0) > 0) history.back();
      else navigateTo(returnPath, { originPath: state.currentAlgorithm?.path || null });
    }
  }
  if (action === "toggle-wrap") toggleCodeWrap();
}


function renderSidebar() {
  if (!state.manifest) return;
  const activeAlgorithm = algorithmForPath(state.currentPath, history.state?.originPath);
  const fragments = [];
  let matchCount = 0;

  for (const phase of state.manifest.phases) {
    const matches = phase.algorithms.filter((algorithm) => algorithmMatches(algorithm, state.query));
    if (state.query && !matches.length) continue;
    matchCount += matches.length;

    const phaseActive = matches.some((algorithm) => algorithm.path === activeAlgorithm?.path);
    const open = state.query || phaseActive || state.openPhases.has(phase.number);
    const phaseCompleted = phase.algorithms.filter((algorithm) => state.completed.has(algorithm.path)).length;
    fragments.push(`
      <section class="phase-group${open ? " open" : ""}">
        <button class="phase-summary" type="button" data-phase-number="${phase.number}" aria-expanded="${open}">
          <span class="phase-number">${String(phase.number).padStart(2, "0")}</span>
          <span class="phase-title">${escapeHtml(phase.title)}</span>
          <span class="phase-chevron" aria-hidden="true">›</span>
        </button>
        <div class="phase-items">
          ${matches.map((algorithm) => renderSidebarAlgorithm(algorithm, activeAlgorithm, phaseCompleted)).join("")}
        </div>
      </section>
    `);
  }

  elements.phaseNavigation.innerHTML = fragments.join("");
  elements.sidebarEmpty.hidden = matchCount !== 0;
  elements.searchResultCount.textContent = state.query ? `${matchCount}개` : "";
  elements.studyNavButton.classList.toggle("active", state.currentPath === STUDY_PATH);

  requestAnimationFrame(() => {
    elements.phaseNavigation.querySelector(".phase-item.active")?.scrollIntoView({ block: "nearest" });
  });
}


function renderSidebarAlgorithm(algorithm, activeAlgorithm) {
  const checked = state.completed.has(algorithm.path);
  const active = activeAlgorithm?.path === algorithm.path;
  return `
    <div class="phase-item${active ? " active" : ""}">
      <button class="progress-toggle${checked ? " checked" : ""}" type="button" role="checkbox" aria-label="${escapeAttribute(algorithm.label)} 복원 완료 표시" aria-checked="${checked}" data-progress-path="${escapeAttribute(algorithm.path)}">${checked ? "✓" : ""}</button>
      <button class="phase-item-link" type="button" data-document-path="${escapeAttribute(algorithm.path)}" ${active ? 'aria-current="page"' : ""}>
        <span class="phase-item-label">${escapeHtml(algorithm.label)}</span>
        <span class="phase-item-index">${String(algorithm.index + 1).padStart(2, "0")}</span>
      </button>
    </div>
  `;
}


function algorithmMatches(algorithm, query) {
  if (!query) return true;
  return algorithm.searchText.includes(query)
    || algorithm.title.toLocaleLowerCase("ko").includes(query)
    || algorithm.group.toLocaleLowerCase("en").includes(query);
}


async function renderPath(path, options = {}) {
  const token = ++state.routeToken;
  state.currentPath = normalizePath(path || STUDY_PATH);

  showLoading();
  renderSidebar();

  try {
    const data = await loadDocument(state.currentPath);
    if (token !== state.routeToken) return;

    state.currentPath = data.path;
    state.currentAlgorithm = algorithmForPath(data.path, history.state?.originPath);
    if (state.currentAlgorithm) {
      state.visited.add(state.currentAlgorithm.path);
      saveSet(STORAGE.visited, state.visited);
      localStorage.setItem(STORAGE.lastRoute, state.currentAlgorithm.path);
      state.openPhases.add(state.currentAlgorithm.phase);
    }

    state.copyBlocks = [];
    renderToolbar(data);
    renderSidebar();

    if (data.extension === ".md") renderMarkdownDocument(data);
    else renderSourceDocument(data);

    showDocument();
    renderPagination(data);
    document.title = `${displayName(data)} · BOJ Theory Map`;

    requestAnimationFrame(() => {
      const targetScroll = Number(options.restoreScroll) || 0;
      window.scrollTo(0, targetScroll);
      requestAnimationFrame(() => window.scrollTo(0, targetScroll));
      if (options.focus !== false) elements.documentView.focus({ preventScroll: true });
      setupTocObserver();
    });
  } catch (error) {
    if (token !== state.routeToken) return;
    renderToolbar({ path: state.currentPath, name: state.currentPath });
    showError(error.message || "문서를 열 수 없습니다.");
  }
}


function renderMarkdownDocument(data) {
  const isStudy = data.path === STUDY_PATH;
  const isProblem = isProblemDocumentPath(data.path);
  let markdown = data.content;
  let prefix = "";

  if (isStudy) {
    markdown = markdown.replace(/^#\s+.+?(?:\r?\n)+/u, "");
    const completed = state.manifest.algorithms.filter((algorithm) => state.completed.has(algorithm.path)).length;
    const next = nextIncompleteAlgorithm();
    prefix = `
      <section class="doc-hero">
        <span class="hero-kicker">ALGORITHM MEMORY ROUTE</span>
        <h1>알고리즘 기억 복원 지도</h1>
        <p>파일을 찾아다니지 않고, 순서대로 읽고 구현하고 본인 코드까지 한 화면에서 왕복합니다.</p>
        <div class="hero-actions">
          <button class="primary-button" type="button" data-action="continue">${next ? `${escapeHtml(next.label)}부터 이어보기` : "전체 복습 다시 보기"}</button>
          <button class="secondary-button" type="button" data-doc-path="MISSING_SOLVED_NON_BRONZE.md">코드 없는 해결 문제 보기</button>
        </div>
      </section>
      <section class="study-stats" aria-label="학습 현황">
        <div class="study-stat"><span>PHASES</span><strong>${state.manifest.phaseCount}</strong></div>
        <div class="study-stat"><span>ALGORITHMS</span><strong>${state.manifest.algorithmCount}</strong></div>
        <div class="study-stat"><span>RESTORED</span><strong>${completed}</strong></div>
      </section>
    `;
  } else if (isProblem) {
    prefix = renderProblemContext(data);
  }

  const rendered = renderMarkdown(markdown, data.path);
  elements.documentView.innerHTML = `${prefix}<div class="markdown-body">${rendered.html}</div>`;
  renderToc(rendered.headings);
}


function renderSourceDocument(data) {
  const parentAlgorithm = state.currentAlgorithm;
  const empty = data.content.length === 0;
  const lines = empty ? [] : data.content.replace(/\r\n/g, "\n").split("\n");
  const copyIndex = storeCopyBlock(data.content);
  const parentLink = parentAlgorithm
    ? `<button class="source-parent-link" type="button" data-action="source-parent" data-parent-path="${escapeAttribute(parentAlgorithm.path)}">← ${escapeHtml(parentAlgorithm.label)} 노트로 돌아가기</button>`
    : "";

  elements.documentView.innerHTML = `
    ${parentLink}
    ${renderProblemBridge(data)}
    <section class="source-viewer${state.codeWrap ? " wrap" : ""}">
      <header class="source-header">
        <div class="source-meta">
          <span class="source-language">${escapeHtml(sourceLanguage(data.extension))}</span>
          <span class="source-name">${escapeHtml(data.path)} · ${formatBytes(data.size)}</span>
        </div>
        <div class="source-actions">
          <button type="button" data-action="toggle-wrap">${state.codeWrap ? "줄바꿈 끄기" : "줄바꿈"}</button>
          <button type="button" data-copy-index="${copyIndex}">전체 복사</button>
        </div>
      </header>
      ${empty
        ? `<div class="empty-source"><strong>빈 소스 파일입니다.</strong><span>CORE.md에 기록된 예외 설명을 확인해 주세요.</span></div>`
        : `<div class="source-code" role="region" aria-label="${escapeAttribute(data.name)} 소스 코드" tabindex="0">${lines.map(renderSourceLine).join("")}</div>`}
    </section>
  `;
  elements.documentToc.innerHTML = "";
}


function renderProblemBridge(data) {
  const problem = data.problem;
  if (!problem) return "";

  const localButton = problem.available && problem.path
    ? `<button class="problem-primary-action" type="button" data-doc-path="${escapeAttribute(problem.path)}" data-return-path="${escapeAttribute(data.path)}">문제 설명 보기</button>`
    : `<a class="problem-primary-action" href="${escapeAttribute(problem.officialUrl)}" target="_blank" rel="noopener noreferrer">백준에서 문제 보기 ↗</a>`;
  const officialLink = problem.available
    ? `<a class="problem-secondary-action" href="${escapeAttribute(problem.officialUrl)}" target="_blank" rel="noopener noreferrer">백준 원문 ↗</a>`
    : "";
  const status = problem.available
    ? "저장된 문제·입력·출력·제한을 웹 안에서 확인할 수 있습니다."
    : "저장된 문제 설명이 없어 백준 원문으로 연결합니다.";

  return `
    <section class="problem-bridge" aria-label="${problem.number}번 문제 확인">
      <div class="problem-bridge-copy">
        <span class="problem-kicker">PROBLEM · ${problem.number}</span>
        <strong>${escapeHtml(problem.title)}</strong>
        <p>${status}</p>
      </div>
      <div class="problem-bridge-actions">
        ${localButton}
        ${officialLink}
      </div>
    </section>
  `;
}


function renderProblemContext(data) {
  const problem = data.problem;
  if (!problem) return "";

  const storedReturnPath = normalizePath(history.state?.returnPath || "");
  const validStoredReturn = problemNumberFromPath(storedReturnPath) === problem.number ? storedReturnPath : null;
  const returnPath = validStoredReturn || sourceForProblemNumber(problem.number);
  const returnButton = returnPath
    ? `<button type="button" data-action="problem-return" data-return-path="${escapeAttribute(returnPath)}">${validStoredReturn ? "← 풀이 코드로 돌아가기" : "풀이 코드 보기"}</button>`
    : "";

  return `
    <nav class="problem-context" aria-label="문제와 풀이 이동">
      <div>
        <span>LOCAL PROBLEM · ${problem.number}</span>
        <strong>문제 조건을 확인한 뒤 내 풀이로 돌아갈 수 있습니다.</strong>
      </div>
      <div class="problem-context-actions">
        ${returnButton}
        <a href="${escapeAttribute(problem.officialUrl)}" target="_blank" rel="noopener noreferrer">백준 원문 ↗</a>
      </div>
    </nav>
  `;
}


function renderSourceLine(line, index) {
  return `<div class="source-line"><span class="source-line-number">${index + 1}</span><span class="source-line-code">${escapeHtml(line) || " "}</span></div>`;
}


function renderToolbar(data) {
  const algorithm = algorithmForPath(data.path, history.state?.originPath);
  const isSource = data.extension && data.extension !== ".md";
  const isProblem = isProblemDocumentPath(data.path);
  let breadcrumb;

  if (data.path === STUDY_PATH) {
    breadcrumb = "학습 순서 / <strong>전체 지도</strong>";
  } else if (algorithm) {
    const detail = isSource
      ? data.name
      : isProblem
        ? `${data.problem?.number || ""}번 문제`
        : null;
    breadcrumb = `${String(algorithm.phase).padStart(2, "0")}단계 / ${escapeHtml(algorithm.label)}${detail ? ` / <strong>${escapeHtml(detail)}</strong>` : ""}`;
  } else {
    breadcrumb = `문서 / <strong>${escapeHtml(data.name || data.path)}</strong>`;
  }

  elements.breadcrumb.innerHTML = breadcrumb;
  elements.completeButton.hidden = !algorithm;
  if (algorithm) {
    const completed = state.completed.has(algorithm.path);
    elements.completeButton.classList.toggle("completed", completed);
    elements.completeButton.setAttribute("aria-pressed", String(completed));
    elements.completeButton.querySelector("span:last-child").textContent = completed ? "복원됨" : "복원 완료";
  }
}


function renderPagination(data) {
  const algorithm = algorithmForPath(data.path, history.state?.originPath);
  const show = Boolean(algorithm && data.path === algorithm.path);
  elements.documentPagination.hidden = !show;
  if (!show) return;

  const previous = state.manifest.algorithms[algorithm.index - 1] || null;
  const next = state.manifest.algorithms[algorithm.index + 1] || null;
  setPageButton(elements.previousButton, previous, "PREVIOUS", "이전 알고리즘");
  setPageButton(elements.nextButton, next, "NEXT", "다음 알고리즘");
}


function setPageButton(button, algorithm, direction, fallback) {
  button.disabled = !algorithm;
  button.dataset.documentPath = algorithm?.path || "";
  button.innerHTML = algorithm
    ? `<span class="page-direction">${direction} · ${String(algorithm.index + 1).padStart(2, "0")}</span><span class="page-title">${escapeHtml(algorithm.label)}</span>`
    : `<span class="page-direction">${direction}</span><span class="page-title">${fallback} 없음</span>`;
}


function navigateAdjacent(offset) {
  const algorithm = state.currentAlgorithm;
  if (!algorithm || state.currentPath !== algorithm.path) return;
  const target = state.manifest.algorithms[algorithm.index + offset];
  if (target) navigateTo(target.path);
}


function renderToc(headings) {
  const visible = headings.filter((heading) => heading.level >= 2 && heading.level <= 3);
  if (!visible.length) {
    elements.documentToc.innerHTML = "";
    return;
  }
  elements.documentToc.innerHTML = `
    <span class="toc-label">ON THIS PAGE</span>
    ${visible.map((heading) => `<a class="toc-link level-${heading.level}" href="#${escapeAttribute(heading.id)}">${escapeHtml(heading.text.replace(/^\d+\.\s*/u, ""))}</a>`).join("")}
  `;
}


function setupTocObserver() {
  state.tocObserver?.disconnect();
  const links = [...elements.documentToc.querySelectorAll(".toc-link")];
  if (!links.length || !("IntersectionObserver" in window)) return;

  const byId = new Map(links.map((link) => [link.getAttribute("href").slice(1), link]));
  state.tocObserver = new IntersectionObserver((entries) => {
    const visible = entries.filter((entry) => entry.isIntersecting).sort((a, b) => a.boundingClientRect.top - b.boundingClientRect.top);
    if (!visible.length) return;
    links.forEach((link) => link.classList.remove("active"));
    byId.get(visible[0].target.id)?.classList.add("active");
  }, { rootMargin: "-18% 0px -72% 0px", threshold: 0 });

  for (const id of byId.keys()) {
    const heading = document.getElementById(id);
    if (heading) state.tocObserver.observe(heading);
  }
}


function renderMarkdown(markdown, basePath) {
  const lines = markdown.replace(/\r\n/g, "\n").split("\n");
  const headings = [];
  const usedIds = new Map();
  const output = [];
  let index = 0;

  while (index < lines.length) {
    const line = lines[index];
    if (!line.trim()) {
      index += 1;
      continue;
    }

    const fence = line.match(/^```([^\s]*)\s*$/u);
    if (fence) {
      const language = fence[1] || "text";
      const code = [];
      index += 1;
      while (index < lines.length && !/^```\s*$/u.test(lines[index])) {
        code.push(lines[index]);
        index += 1;
      }
      if (index < lines.length) index += 1;
      output.push(renderCodeBlock(code.join("\n"), language));
      continue;
    }

    const heading = line.match(/^(#{1,4})\s+(.+?)\s*$/u);
    if (heading) {
      const level = heading[1].length;
      const text = stripInlineMarkdown(heading[2]);
      const id = uniqueSlug(text, usedIds);
      headings.push({ level, text, id });
      output.push(`<h${level} id="${escapeAttribute(id)}">${renderInline(heading[2], basePath)}</h${level}>`);
      index += 1;
      continue;
    }

    if (/^\s*(?:---+|___+|\*\*\*+)\s*$/u.test(line)) {
      output.push("<hr>");
      index += 1;
      continue;
    }

    if (line.startsWith(">")) {
      const quoted = [];
      while (index < lines.length && lines[index].startsWith(">")) {
        quoted.push(lines[index].replace(/^>\s?/u, ""));
        index += 1;
      }
      output.push(`<blockquote><p>${renderInline(quoted.join(" "), basePath)}</p></blockquote>`);
      continue;
    }

    if (isTableStart(lines, index)) {
      const table = renderTable(lines, index, basePath);
      output.push(table.html);
      index = table.nextIndex;
      continue;
    }

    const unordered = line.match(/^\s*[-*]\s+(.+)$/u);
    const ordered = line.match(/^\s*(\d+)\.\s+(.+)$/u);
    if (unordered || ordered) {
      const list = renderList(lines, index, basePath, Boolean(ordered));
      output.push(list.html);
      index = list.nextIndex;
      continue;
    }

    const paragraph = [line.trim()];
    index += 1;
    while (index < lines.length && lines[index].trim() && !isBlockStart(lines, index)) {
      paragraph.push(lines[index].trim());
      index += 1;
    }
    output.push(`<p>${renderInline(paragraph.join(" "), basePath)}</p>`);
  }

  return { html: output.join("\n"), headings };
}


function renderList(lines, startIndex, basePath, ordered) {
  const items = [];
  let index = startIndex;
  const pattern = ordered ? /^\s*(\d+)\.\s+(.+)$/u : /^\s*[-*]\s+(.+)$/u;
  const startMatch = lines[startIndex].match(pattern);
  const start = ordered ? Number.parseInt(startMatch[1], 10) : null;
  let hasTasks = false;

  while (index < lines.length) {
    const match = lines[index].match(pattern);
    if (!match) break;
    const raw = match[ordered ? 2 : 1];
    const task = raw.match(/^\[([ xX])\]\s+(.+)$/u);
    if (task) {
      hasTasks = true;
      const body = task[2];
      const link = body.match(/\[[^\]]+\]\(([^)]+)\)/u);
      const resolved = link ? resolveDocPath(basePath, link[1]) : "";
      const checked = Boolean(resolved && state.completed.has(resolved));
      items.push(`<li class="task-item"><button class="task-checkbox${checked ? " checked" : ""}" type="button" role="checkbox" aria-checked="${checked}" data-task-path="${escapeAttribute(resolved)}">${checked ? "✓" : ""}</button><span>${renderInline(body, basePath)}</span></li>`);
    } else {
      items.push(`<li>${renderInline(raw, basePath)}</li>`);
    }
    index += 1;
  }

  const tag = ordered ? "ol" : "ul";
  const attributes = `${ordered && start !== 1 ? ` start="${start}"` : ""}${hasTasks ? ' class="task-list"' : ""}`;
  return { html: `<${tag}${attributes}>${items.join("")}</${tag}>`, nextIndex: index };
}


function isBlockStart(lines, index) {
  const line = lines[index];
  return !line.trim()
    || /^```/u.test(line)
    || /^#{1,4}\s+/u.test(line)
    || /^\s*(?:---+|___+|\*\*\*+)\s*$/u.test(line)
    || line.startsWith(">")
    || /^\s*[-*]\s+/u.test(line)
    || /^\s*\d+\.\s+/u.test(line)
    || isTableStart(lines, index);
}


function isTableStart(lines, index) {
  if (index + 1 >= lines.length || !lines[index].includes("|")) return false;
  return /^\s*\|?\s*:?-{3,}:?\s*(?:\|\s*:?-{3,}:?\s*)+\|?\s*$/u.test(lines[index + 1]);
}


function renderTable(lines, startIndex, basePath) {
  const headers = splitTableRow(lines[startIndex]);
  const rows = [];
  let index = startIndex + 2;
  while (index < lines.length && lines[index].trim() && lines[index].includes("|")) {
    rows.push(splitTableRow(lines[index]));
    index += 1;
  }

  const head = headers.map((cell) => `<th>${renderInline(cell, basePath)}</th>`).join("");
  const body = rows.map((row) => `<tr>${headers.map((_, cellIndex) => `<td>${renderInline(row[cellIndex] || "", basePath)}</td>`).join("")}</tr>`).join("");
  return {
    html: `<div class="table-scroll" role="region" aria-label="문서 표" tabindex="0"><table><thead><tr>${head}</tr></thead><tbody>${body}</tbody></table></div>`,
    nextIndex: index,
  };
}


function splitTableRow(line) {
  return line.trim().replace(/^\|/u, "").replace(/\|$/u, "").split("|").map((cell) => cell.trim());
}


function renderInline(text, basePath) {
  const tokens = [];
  const storeToken = (html) => {
    const marker = `\uE000${tokens.length}\uE001`;
    tokens.push(html);
    return marker;
  };

  let value = String(text);
  value = value.replace(/`([^`]+)`/gu, (_, code) => storeToken(`<code>${escapeHtml(code)}</code>`));
  value = value.replace(/\[([^\]]+)\]\(([^)]+)\)/gu, (_, label, href) => storeToken(renderLink(label, href, basePath)));
  value = escapeHtml(value);
  value = value.replace(/\*\*(.+?)\*\*/gu, "<strong>$1</strong>");
  value = value.replace(/~~(.+?)~~/gu, "<del>$1</del>");
  value = value.replace(/\uE000(\d+)\uE001/gu, (_, index) => tokens[Number.parseInt(index, 10)] || "");
  return value;
}


function renderLink(label, href, basePath) {
  if (/^https?:\/\//iu.test(href)) {
    return `<a href="${escapeAttribute(href)}" target="_blank" rel="noopener noreferrer">${escapeHtml(label)} ↗</a>`;
  }
  if (/^(?:mailto:|tel:)/iu.test(href)) {
    return `<a href="${escapeAttribute(href)}">${escapeHtml(label)}</a>`;
  }
  if (href.startsWith("#")) {
    return `<a href="${escapeAttribute(href)}">${escapeHtml(label)}</a>`;
  }
  const resolved = resolveDocPath(basePath, href);
  return `<a href="${routeHash(resolved)}" data-doc-path="${escapeAttribute(resolved)}">${escapeHtml(label)}</a>`;
}


function renderCodeBlock(code, language) {
  const copyIndex = storeCopyBlock(code);
  return `
    <div class="code-block">
      <div class="code-toolbar"><span>${escapeHtml(language || "text")}</span><button type="button" data-copy-index="${copyIndex}">복사</button></div>
      <pre><code>${escapeHtml(code)}</code></pre>
    </div>
  `;
}


function storeCopyBlock(code) {
  const index = state.copyBlocks.length;
  state.copyBlocks.push(code);
  return index;
}


function stripInlineMarkdown(value) {
  return value
    .replace(/\[([^\]]+)\]\([^)]+\)/gu, "$1")
    .replace(/[`*_~]/gu, "")
    .trim();
}


function uniqueSlug(text, usedIds) {
  const base = text
    .toLocaleLowerCase("ko")
    .replace(/[^\p{L}\p{N}]+/gu, "-")
    .replace(/^-+|-+$/gu, "") || "section";
  const count = usedIds.get(base) || 0;
  usedIds.set(base, count + 1);
  return count ? `${base}-${count + 1}` : base;
}


function navigateTo(path, options = {}) {
  const normalized = normalizePath(path || STUDY_PATH);
  if (normalized === state.currentPath && !options.force) {
    setSidebarOpen(false);
    return;
  }

  rememberScrollNow();
  const currentIndex = Number(history.state?.index) || 0;
  history.pushState(
    {
      app: true,
      index: currentIndex + 1,
      path: normalized,
      scroll: 0,
      originPath: options.originPath || null,
      returnPath: options.returnPath || null,
    },
    "",
    routeHash(normalized),
  );
  setSidebarOpen(false);
  renderPath(normalized, { restoreScroll: 0 });
}


function goBack() {
  if ((Number(history.state?.index) || 0) > 0) history.back();
  else if (state.currentPath !== STUDY_PATH) navigateTo(STUDY_PATH);
  else window.scrollTo({ top: 0, behavior: "smooth" });
}


function routeHash(path) {
  return path === STUDY_PATH ? "#/study" : `#/doc/${encodeURIComponent(normalizePath(path))}`;
}


function pathFromHash() {
  const prefix = "#/doc/";
  if (location.hash.startsWith(prefix)) {
    try {
      return normalizePath(decodeURIComponent(location.hash.slice(prefix.length)));
    } catch {
      return STUDY_PATH;
    }
  }
  return STUDY_PATH;
}


function resolveDocPath(basePath, href) {
  const cleanHref = href.split("#", 1)[0].replaceAll("\\", "/");
  if (!cleanHref) return normalizePath(basePath);
  const base = normalizePath(basePath).split("/");
  base.pop();
  for (const part of cleanHref.split("/")) {
    if (!part || part === ".") continue;
    if (part === "..") base.pop();
    else base.push(part);
  }
  return normalizePath(base.join("/"));
}


function normalizePath(value) {
  return String(value || "").replaceAll("\\", "/").replace(/^\.\//u, "").replace(/\/+/gu, "/");
}


function algorithmForPath(path, originPath = null) {
  if (!state.manifest || !path) return null;
  const normalized = normalizePath(path);
  const direct = state.manifest.algorithms.find((algorithm) => algorithm.path === normalized);
  if (direct) return direct;

  if (originPath) {
    const origin = state.manifest.algorithms.find((algorithm) => algorithm.path === normalizePath(originPath));
    if (origin) return origin;
  }

  if (normalized.startsWith("TAG/")) {
    const sourceOwner = state.manifest.algorithms.find((algorithm) => algorithm.sourceFiles.includes(normalized));
    if (sourceOwner) return sourceOwner;

    const directory = normalized.slice(0, normalized.lastIndexOf("/") + 1);
    return state.manifest.algorithms.find((algorithm) => algorithm.path.startsWith(directory)) || null;
  }

  if (isProblemDocumentPath(normalized)) {
    const problemNumber = problemNumberFromPath(normalized);
    return state.manifest.algorithms.find((algorithm) => (
      algorithm.sourceFiles.some((sourcePath) => problemNumberFromPath(sourcePath) === problemNumber)
    )) || null;
  }

  return null;
}


function problemNumberFromPath(pathValue) {
  const fileName = normalizePath(pathValue).split("/").at(-1) || "";
  const match = fileName.match(/^(\d{4,})/u);
  return match ? Number.parseInt(match[1], 10) : null;
}


function isProblemDocumentPath(pathValue) {
  return /^BOJ\/(?:1-10000|10001-20000|20001-30000|30001-40000)\/\d{4,5}\.md$/u.test(normalizePath(pathValue));
}


function sourceForProblemNumber(problemNumber) {
  const preferred = state.currentAlgorithm
    ? [state.currentAlgorithm, ...state.manifest.algorithms.filter((algorithm) => algorithm.path !== state.currentAlgorithm.path)]
    : state.manifest.algorithms;
  for (const algorithm of preferred) {
    const sourcePath = algorithm.sourceFiles.find((candidate) => problemNumberFromPath(candidate) === problemNumber);
    if (sourcePath) return sourcePath;
  }
  return null;
}


function continueStudy() {
  const next = nextIncompleteAlgorithm() || state.manifest.algorithms[0];
  if (next) navigateTo(next.path);
}


function nextIncompleteAlgorithm() {
  if (!state.manifest) return null;
  const lastPath = localStorage.getItem(STORAGE.lastRoute);
  const last = state.manifest.algorithms.find((algorithm) => algorithm.path === lastPath);
  if (last && !state.completed.has(last.path)) return last;
  if (last) {
    const later = state.manifest.algorithms.slice(last.index + 1).find((algorithm) => !state.completed.has(algorithm.path));
    if (later) return later;
  }
  return state.manifest.algorithms.find((algorithm) => !state.completed.has(algorithm.path)) || null;
}


function toggleCurrentComplete() {
  if (state.currentAlgorithm) toggleProgress(state.currentAlgorithm.path);
}


function toggleProgress(path) {
  if (!path) return;
  if (state.completed.has(path)) state.completed.delete(path);
  else state.completed.add(path);
  saveSet(STORAGE.completed, state.completed);
  updateProgressUI();
  renderSidebar();
  updateProgressButtonsInDocument(path);
  if (state.currentAlgorithm?.path === path) renderToolbar({ path: state.currentPath, name: state.currentPath, extension: extensionOf(state.currentPath) });
}


function updateProgressButtonsInDocument(path) {
  const checked = state.completed.has(path);
  elements.documentView.querySelectorAll(`[data-task-path="${cssEscape(path)}"]`).forEach((button) => {
    button.classList.toggle("checked", checked);
    button.setAttribute("aria-checked", String(checked));
    button.textContent = checked ? "✓" : "";
  });
}


function updateProgressUI() {
  if (!state.manifest) return;
  const total = state.manifest.algorithmCount;
  const completed = state.manifest.algorithms.filter((algorithm) => state.completed.has(algorithm.path)).length;
  const percent = total ? Math.round((completed / total) * 100) : 0;
  elements.progressCircle.setAttribute("stroke-dashoffset", String(100 - percent));
  elements.progressPercent.textContent = `${percent}%`;
  elements.progressCount.textContent = `${completed} / ${total} 완료`;
  elements.topProgressLabel.textContent = `${completed} / ${total}`;
  const next = nextIncompleteAlgorithm();
  elements.continueButton.textContent = next ? `${next.label} 이어보기 →` : "전체 복습 다시 보기 →";
}


async function reloadCurrentDocument() {
  if (!state.currentPath) return;
  state.documentCache.delete(state.currentPath);
  const scroll = window.scrollY;
  await renderPath(state.currentPath, { restoreScroll: scroll, focus: false });
  showToast("원본 파일을 다시 읽었습니다.");
}


function toggleCodeWrap() {
  state.codeWrap = !state.codeWrap;
  localStorage.setItem(STORAGE.codeWrap, String(state.codeWrap));
  const viewer = elements.documentView.querySelector(".source-viewer");
  if (viewer) {
    viewer.classList.toggle("wrap", state.codeWrap);
    const button = viewer.querySelector('[data-action="toggle-wrap"]');
    if (button) button.textContent = state.codeWrap ? "줄바꿈 끄기" : "줄바꿈";
  }
}


async function loadDocument(path) {
  const normalized = normalizePath(path);
  if (state.documentCache.has(normalized)) return state.documentCache.get(normalized);
  const data = await fetchJson(`/api/file?path=${encodeURIComponent(normalized)}`);
  state.documentCache.set(normalized, data);
  return data;
}


async function fetchJson(url) {
  const response = await fetch(url, { cache: "no-store" });
  let payload;
  try {
    payload = await response.json();
  } catch {
    throw new Error("로컬 서버의 응답을 읽지 못했습니다.");
  }
  if (!response.ok) throw new Error(payload.error || `요청 실패 (${response.status})`);
  return payload;
}


function rememberScrollPosition() {
  if (state.scrollFrame) return;
  state.scrollFrame = requestAnimationFrame(() => {
    rememberScrollNow();
    state.scrollFrame = null;
  });
}


function rememberScrollNow() {
  if (!history.state?.app) return;
  history.replaceState({ ...history.state, scroll: window.scrollY }, "", location.href);
}


function showLoading() {
  elements.loadingView.hidden = false;
  elements.errorView.hidden = true;
  elements.readerLayout.hidden = true;
  elements.documentPagination.hidden = true;
}


function showDocument() {
  elements.loadingView.hidden = true;
  elements.errorView.hidden = true;
  elements.readerLayout.hidden = false;
}


function showError(message) {
  elements.loadingView.hidden = true;
  elements.readerLayout.hidden = true;
  elements.documentPagination.hidden = true;
  elements.errorView.hidden = false;
  elements.errorMessage.textContent = message;
}


function setSidebarOpen(open) {
  elements.sidebar.classList.toggle("open", open);
  elements.sidebarBackdrop.hidden = !open;
  elements.menuButton.setAttribute("aria-expanded", String(open));
  document.body.style.overflow = open ? "hidden" : "";
}


function applySavedTheme() {
  const saved = localStorage.getItem(STORAGE.theme);
  const preferred = window.matchMedia?.("(prefers-color-scheme: light)").matches ? "light" : "dark";
  setTheme(saved || preferred);
}


function toggleTheme() {
  setTheme(document.documentElement.dataset.theme === "dark" ? "light" : "dark");
}


function setTheme(theme) {
  document.documentElement.dataset.theme = theme;
  localStorage.setItem(STORAGE.theme, theme);
  elements.themeButton?.setAttribute("aria-label", theme === "dark" ? "밝은 화면으로 전환" : "어두운 화면으로 전환");
  document.querySelector('meta[name="theme-color"]')?.setAttribute("content", theme === "dark" ? "#081521" : "#f3f0e8");
}


async function copyText(value) {
  if (navigator.clipboard?.writeText) {
    await navigator.clipboard.writeText(value);
    return;
  }
  const textarea = document.createElement("textarea");
  textarea.value = value;
  textarea.style.position = "fixed";
  textarea.style.opacity = "0";
  document.body.append(textarea);
  textarea.select();
  document.execCommand("copy");
  textarea.remove();
}


function showToast(message) {
  clearTimeout(state.toastTimer);
  elements.toast.textContent = message;
  elements.toast.classList.add("show");
  state.toastTimer = setTimeout(() => elements.toast.classList.remove("show"), 1800);
}


function displayName(data) {
  if (data.path === STUDY_PATH) return "학습 순서";
  if (isProblemDocumentPath(data.path)) return data.problem?.title || data.name || "문제 설명";
  return state.currentAlgorithm?.label || data.name || "문서";
}


function sourceLanguage(extension) {
  if ([".cpp", ".cc", ".c", ".hpp", ".h"].includes(extension)) return "C++";
  if (extension === ".md") return "Markdown";
  return "TEXT";
}


function formatBytes(bytes) {
  if (bytes < 1024) return `${bytes} B`;
  return `${(bytes / 1024).toFixed(1)} KB`;
}


function extensionOf(pathValue) {
  const fileName = pathValue.split("/").at(-1) || "";
  const dot = fileName.lastIndexOf(".");
  return dot >= 0 ? fileName.slice(dot).toLocaleLowerCase("en") : "";
}


function loadSet(key) {
  try {
    const value = JSON.parse(localStorage.getItem(key) || "[]");
    return new Set(Array.isArray(value) ? value : []);
  } catch {
    return new Set();
  }
}


function saveSet(key, value) {
  localStorage.setItem(key, JSON.stringify([...value]));
}


function escapeHtml(value) {
  return String(value)
    .replaceAll("&", "&amp;")
    .replaceAll("<", "&lt;")
    .replaceAll(">", "&gt;")
    .replaceAll('"', "&quot;")
    .replaceAll("'", "&#39;");
}


function escapeAttribute(value) {
  return escapeHtml(value).replaceAll("`", "&#96;");
}


function cssEscape(value) {
  if (window.CSS?.escape) return CSS.escape(value);
  return value.replace(/["\\]/gu, "\\$&");
}


function toCamel(value) {
  return value.replace(/-([a-z])/gu, (_, letter) => letter.toUpperCase());
}
