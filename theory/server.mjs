import { createServer } from "node:http";
import { readFile, realpath, stat } from "node:fs/promises";
import { spawn } from "node:child_process";
import path from "node:path";
import process from "node:process";
import { fileURLToPath } from "node:url";


const THEORY_DIR = path.dirname(fileURLToPath(import.meta.url));
const WORKSPACE_DIR = path.dirname(THEORY_DIR);
const HOST = "127.0.0.1";

const STATIC_FILES = new Map([
  ["/", ["index.html", "text/html; charset=utf-8"]],
  ["/index.html", ["index.html", "text/html; charset=utf-8"]],
  ["/styles.css", ["styles.css", "text/css; charset=utf-8"]],
  ["/app.js", ["app.js", "text/javascript; charset=utf-8"]],
  ["/favicon.svg", ["favicon.svg", "image/svg+xml; charset=utf-8"]],
]);

const PHASE_PATTERN = /^##\s+(\d+)단계\s*[—-]\s*(.+?)\s*$/;
const ALGORITHM_PATTERN = /^-\s+\[[ xX]\]\s+\[([^\]]+)\]\((TAG\/[^)]+\/CORE\.md)\)\s*$/;
const CHECKPOINT_PATTERN = /^\*\*체크포인트:\*\*\s*(.+?)\s*$/;
const HEADING_PATTERN = /^#\s+(.+?)\s*$/m;
const SOURCE_LINK_PATTERN = /\[[^\]]+\]\(([^)#]+\.(?:cpp|cc|c|hpp|h|txt))(?:#[^)]*)?\)/g;

const CSP = [
  "default-src 'self'",
  "script-src 'self'",
  "style-src 'self'",
  "connect-src 'self'",
  "img-src 'self' data:",
  "object-src 'none'",
  "base-uri 'none'",
  "frame-ancestors 'none'",
].join("; ");


function parseArguments() {
  const args = process.argv.slice(2);
  let port = 8765;
  let openBrowser = true;

  for (let index = 0; index < args.length; index += 1) {
    if (args[index] === "--port" && args[index + 1]) {
      port = Number.parseInt(args[index + 1], 10);
      index += 1;
    } else if (args[index] === "--no-browser") {
      openBrowser = false;
    }
  }

  if (!Number.isInteger(port) || port < 0 || port > 65535) {
    throw new Error("포트는 0부터 65535 사이의 정수여야 합니다.");
  }
  return { port, openBrowser };
}


function responseHeaders(contentType) {
  return {
    "Cache-Control": "no-store",
    "Content-Type": contentType,
    "Content-Security-Policy": CSP,
    "Referrer-Policy": "no-referrer",
    "X-Content-Type-Options": "nosniff",
  };
}


function sendJson(response, statusCode, value) {
  const body = Buffer.from(JSON.stringify(value), "utf8");
  response.writeHead(statusCode, {
    ...responseHeaders("application/json; charset=utf-8"),
    "Content-Length": body.length,
  });
  response.end(body);
}


function sendText(response, statusCode, text) {
  const body = Buffer.from(text, "utf8");
  response.writeHead(statusCode, {
    ...responseHeaders("text/plain; charset=utf-8"),
    "Content-Length": body.length,
  });
  response.end(body);
}


function toPosix(relativePath) {
  return relativePath.split(path.sep).join("/");
}


function normalizeRelativeLink(basePath, href) {
  const cleanHref = href.split("#", 1)[0].replaceAll("\\", "/");
  const baseDirectory = path.posix.dirname(basePath);
  return path.posix.normalize(path.posix.join(baseDirectory, cleanHref));
}


function problemBucket(problemNumber) {
  if (problemNumber <= 10000) return "1-10000";
  if (problemNumber <= 20000) return "10001-20000";
  if (problemNumber <= 30000) return "20001-30000";
  if (problemNumber <= 40000) return "30001-40000";
  return null;
}


function problemNumberFromDocument(relativePath) {
  const fileName = path.posix.basename(relativePath);
  const match = fileName.match(/^(\d{4,})/u);
  if (!match) return null;
  const problemNumber = Number.parseInt(match[1], 10);
  return problemNumber >= 1000 && problemBucket(problemNumber) ? problemNumber : null;
}


function isAllowedProblemDocument(relativePath) {
  const match = relativePath.match(/^BOJ\/(1-10000|10001-20000|20001-30000|30001-40000)\/(\d{4,5})\.md$/u);
  if (!match) return false;
  const problemNumber = Number.parseInt(match[2], 10);
  return String(problemNumber) === match[2] && problemBucket(problemNumber) === match[1];
}


function isAllowedDocument(relativePath) {
  if (relativePath === "ALGORITHM_STUDY_ORDER.md") return true;
  if (relativePath === "MISSING_SOLVED_NON_BRONZE.md") return true;
  if (isAllowedProblemDocument(relativePath)) return true;
  return /^TAG\/[A-Za-z0-9_/-]+\/(?:CORE\.md|[^/]+\.(?:cpp|cc|c|hpp|h|txt))$/u.test(relativePath);
}


async function resolveDocument(rawPath) {
  if (!rawPath) {
    const error = new Error("path가 비어 있습니다.");
    error.statusCode = 400;
    throw error;
  }

  let decoded;
  try {
    decoded = decodeURIComponent(rawPath);
  } catch {
    const error = new Error("경로 인코딩이 올바르지 않습니다.");
    error.statusCode = 400;
    throw error;
  }

  decoded = decoded.replaceAll("\\", "/");
  if (
    decoded.includes("\0")
    || decoded.startsWith("/")
    || decoded.startsWith("//")
    || /^[A-Za-z]:\//u.test(decoded)
  ) {
    const error = new Error("절대 경로는 열 수 없습니다.");
    error.statusCode = 403;
    throw error;
  }

  const normalized = path.posix.normalize(decoded);
  if (normalized === ".." || normalized.startsWith("../") || !isAllowedDocument(normalized)) {
    const error = new Error("학습 문서, BOJ 문제 설명과 TAG 소스 코드만 열 수 있습니다.");
    error.statusCode = 403;
    throw error;
  }

  const candidate = path.resolve(WORKSPACE_DIR, ...normalized.split("/"));
  const relativeFromRoot = path.relative(WORKSPACE_DIR, candidate);
  if (relativeFromRoot.startsWith("..") || path.isAbsolute(relativeFromRoot)) {
    const error = new Error("워크스페이스 밖의 파일은 열 수 없습니다.");
    error.statusCode = 403;
    throw error;
  }

  let resolved;
  try {
    resolved = await realpath(candidate);
  } catch {
    const error = new Error("파일을 찾을 수 없습니다.");
    error.statusCode = 404;
    throw error;
  }

  const realRelative = path.relative(await realpath(WORKSPACE_DIR), resolved);
  if (realRelative.startsWith("..") || path.isAbsolute(realRelative)) {
    const error = new Error("워크스페이스 밖의 연결은 열 수 없습니다.");
    error.statusCode = 403;
    throw error;
  }

  return { absolutePath: resolved, relativePath: toPosix(realRelative) };
}


async function firstHeading(absolutePath, fallback) {
  try {
    const content = await readFile(absolutePath, "utf8");
    return content.match(HEADING_PATTERN)?.[1]?.trim() || fallback;
  } catch {
    return fallback;
  }
}


async function problemMetadata(relativePath) {
  const problemNumber = problemNumberFromDocument(relativePath);
  if (!problemNumber) return null;

  const bucket = problemBucket(problemNumber);
  const problemPath = `BOJ/${bucket}/${problemNumber}.md`;
  const candidate = path.resolve(WORKSPACE_DIR, ...problemPath.split("/"));
  let available = false;
  let title = `${problemNumber}번 문제`;

  try {
    const resolved = await realpath(candidate);
    const realRelative = toPosix(path.relative(await realpath(WORKSPACE_DIR), resolved));
    if (isAllowedProblemDocument(realRelative)) {
      available = true;
      title = await firstHeading(resolved, title);
    }
  } catch {
    // 저장된 문제 설명이 없으면 공식 문제 페이지를 안내한다.
  }

  return {
    number: problemNumber,
    title,
    available,
    path: available ? problemPath : null,
    officialUrl: `https://www.acmicpc.net/problem/${problemNumber}`,
  };
}


async function buildManifest() {
  const studyPath = path.join(WORKSPACE_DIR, "ALGORITHM_STUDY_ORDER.md");
  const studyText = await readFile(studyPath, "utf8");
  const phases = [];
  let current = null;

  for (const rawLine of studyText.split(/\r?\n/u)) {
    const line = rawLine.trim();
    const phaseMatch = line.match(PHASE_PATTERN);
    if (phaseMatch) {
      current = {
        number: Number.parseInt(phaseMatch[1], 10),
        title: phaseMatch[2].trim(),
        description: "",
        checkpoint: "",
        algorithms: [],
      };
      phases.push(current);
      continue;
    }

    if (!current || !line) continue;

    const algorithmMatch = line.match(ALGORITHM_PATTERN);
    if (algorithmMatch) {
      const label = algorithmMatch[1].trim();
      const relativePath = algorithmMatch[2].replaceAll("\\", "/");
      const absolutePath = path.resolve(WORKSPACE_DIR, ...relativePath.split("/"));
      let coreText = "";
      try {
        coreText = await readFile(absolutePath, "utf8");
      } catch {
        // A missing file stays visible in navigation and opens a useful 404 page.
      }

      const sourceFiles = [];
      for (const match of coreText.matchAll(SOURCE_LINK_PATTERN)) {
        sourceFiles.push(normalizeRelativeLink(relativePath, match[1]));
      }

      const parts = relativePath.split("/");
      current.algorithms.push({
        label,
        title: await firstHeading(absolutePath, label),
        path: relativePath,
        group: parts[1] || "",
        slug: parts.at(-2) || label,
        phase: current.number,
        sourceFiles: [...new Set(sourceFiles)],
        searchText: `${label}\n${coreText}\n${sourceFiles.join("\n")}`.toLocaleLowerCase("ko"),
      });
      continue;
    }

    const checkpointMatch = line.match(CHECKPOINT_PATTERN);
    if (checkpointMatch) {
      current.checkpoint = checkpointMatch[1].trim();
      continue;
    }

    if (!current.algorithms.length && !line.startsWith("#") && !line.startsWith("-") && line !== "---") {
      current.description = `${current.description} ${line}`.trim();
    }
  }

  const algorithms = phases.flatMap((phase) => phase.algorithms);
  algorithms.forEach((algorithm, index) => {
    algorithm.index = index;
  });

  return {
    studyPath: "ALGORITHM_STUDY_ORDER.md",
    missingPath: "MISSING_SOLVED_NON_BRONZE.md",
    phaseCount: phases.length,
    algorithmCount: algorithms.length,
    phases,
    algorithms,
  };
}


async function serveStatic(requestPath, response) {
  const entry = STATIC_FILES.get(requestPath);
  if (!entry) {
    sendText(response, 404, "Not found");
    return;
  }

  const [fileName, contentType] = entry;
  const body = await readFile(path.join(THEORY_DIR, fileName));
  response.writeHead(200, {
    ...responseHeaders(contentType),
    "Content-Length": body.length,
  });
  response.end(body);
}


async function handleRequest(request, response) {
  if (request.method !== "GET") {
    sendJson(response, 405, { error: "GET 요청만 지원합니다." });
    return;
  }

  const requestUrl = new URL(request.url, `http://${HOST}`);

  try {
    if (requestUrl.pathname === "/api/health") {
      sendJson(response, 200, { ok: true, workspace: path.basename(WORKSPACE_DIR) });
      return;
    }

    if (requestUrl.pathname === "/api/manifest") {
      sendJson(response, 200, await buildManifest());
      return;
    }

    if (requestUrl.pathname === "/api/file") {
      const rawPath = requestUrl.searchParams.get("path") || "";
      const { absolutePath, relativePath } = await resolveDocument(rawPath);
      const [content, info, problem] = await Promise.all([
        readFile(absolutePath, "utf8"),
        stat(absolutePath),
        problemMetadata(relativePath),
      ]);
      sendJson(response, 200, {
        path: relativePath,
        name: path.basename(absolutePath),
        extension: path.extname(absolutePath).toLocaleLowerCase("en"),
        content,
        size: info.size,
        modified: info.mtimeMs,
        problem,
      });
      return;
    }

    await serveStatic(requestUrl.pathname, response);
  } catch (error) {
    const statusCode = Number.isInteger(error.statusCode) ? error.statusCode : 500;
    sendJson(response, statusCode, {
      error: statusCode === 500 ? "서버에서 문서를 읽지 못했습니다." : error.message,
    });
    if (statusCode === 500) console.error(error);
  }
}


function openInBrowser(url) {
  let command;
  let args;

  if (process.platform === "win32") {
    command = "cmd.exe";
    args = ["/d", "/s", "/c", "start", "", url];
  } else if (process.platform === "darwin") {
    command = "open";
    args = [url];
  } else {
    command = "xdg-open";
    args = [url];
  }

  const child = spawn(command, args, {
    detached: true,
    stdio: "ignore",
    windowsHide: true,
  });
  child.unref();
}


function listen(server, port) {
  return new Promise((resolve, reject) => {
    const onError = (error) => {
      server.off("listening", onListening);
      reject(error);
    };
    const onListening = () => {
      server.off("error", onError);
      resolve();
    };
    server.once("error", onError);
    server.once("listening", onListening);
    server.listen(port, HOST);
  });
}


async function main() {
  const options = parseArguments();
  let server = createServer((request, response) => {
    handleRequest(request, response);
  });

  try {
    await listen(server, options.port);
  } catch (error) {
    if (error.code !== "EADDRINUSE" || options.port === 0) throw error;
    console.log(`[theory] ${options.port} 포트가 사용 중이라 빈 포트를 찾습니다.`);
    server = createServer((request, response) => {
      handleRequest(request, response);
    });
    await listen(server, 0);
  }

  const address = server.address();
  const actualPort = typeof address === "object" && address ? address.port : options.port;
  const url = `http://${HOST}:${actualPort}/`;

  console.log("=".repeat(64));
  console.log("BOJ Theory Map");
  console.log(`브라우저 주소: ${url}`);
  console.log("종료: 이 창에서 Ctrl+C");
  console.log("=".repeat(64));

  if (options.openBrowser) {
    setTimeout(() => openInBrowser(url), 350);
  }

  const shutdown = () => {
    console.log("\n[theory] 서버를 종료합니다.");
    server.close(() => process.exit(0));
  };
  process.on("SIGINT", shutdown);
  process.on("SIGTERM", shutdown);
}


main().catch((error) => {
  console.error("[theory] 서버를 시작하지 못했습니다.");
  console.error(error);
  process.exit(1);
});
