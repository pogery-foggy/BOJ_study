# 단절점 핵심 복원 노트

## 한 문장 기억

**DFS 자식이 현재 정점보다 위의 조상으로 우회할 수 없다면, 현재 정점을 없앴을 때 그 자식 서브트리가 끊어진다.**

## 언제 꺼내는가

- 무방향 그래프에서 정점 하나를 제거했을 때 연결 요소 수가 늘어나는 정점을 찾는다.
- 다리(단절선), 이중 연결 요소처럼 DFS 트리와 역방향 간선을 분석한다.

## 핵심 상태와 불변식

- `order[u]`: `u`를 처음 방문한 순서.
- `low[u]`: `u`의 서브트리가 트리 간선과 역방향 간선으로 도달 가능한 최소 방문 순서.
- 루트가 아니면 자식 `v`에 대해 `low[v] >= order[u]`일 때 `u`가 단절점이다.
- DFS 루트는 독립적인 DFS 자식이 2개 이상일 때만 단절점이다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [11266.cpp](./11266.cpp)의 전역 `edge`/`visited`/`up_limit`/`is_cut` 배열, `cur`/`nxt` 명명, 자식의 반환값을 `ret`에 받는 재귀 `dfs()` 구조를 그대로 축약했다.

```cpp
#define MAX_N 100001

vector<int> edge[MAX_N];
int visited[MAX_N];
int up_limit[MAX_N];
bool is_cut[MAX_N];
int depth;

int dfs(int cur, int parent) {
    visited[cur] = up_limit[cur] = ++depth;
    int child = 0;

    for (int nxt : edge[cur]) {
        if (nxt == parent) continue;
        if (visited[nxt] == 0) {
            child++;
            int ret = dfs(nxt, cur);
            up_limit[cur] = min(up_limit[cur], ret);
            if (parent != 0 && ret >= visited[cur])
                is_cut[cur] = true;
        } else {
            up_limit[cur] = min(up_limit[cur], visited[nxt]);
        }
    }
    if (parent == 0 && child >= 2)
        is_cut[cur] = true;
    return up_limit[cur];
}
```

## 빈 화면 구현 순서

1. 무방향 인접 리스트를 만든다.
2. 방문 시 `order=low=++timer`를 기록한다.
3. 미방문 자식 DFS 뒤 `low[u]`를 자식의 `low`로 갱신한다.
4. 방문한 이웃은 그 이웃의 `order`로만 `low[u]`를 갱신한다.
5. 일반 정점 조건과 루트 조건을 분리한다.
6. 그래프가 연결되지 않을 수 있으므로 모든 정점에서 DFS를 시작한다.

## 자주 틀리는 지점

- 루트에도 `low[child] >= order[root]` 조건을 그대로 쓰는 것.
- 이미 방문한 이웃에서 `low[v]`를 사용해 잘못 낮추는 것.
- 단순 그래프가 아닐 때 정점 번호만으로 부모 간선을 건너뛰어 평행 간선을 놓치는 것. 이때는 간선 ID를 저장한다.
- 연결 그래프라고 가정하고 1에서만 DFS하는 것.
- 깊은 재귀에서 스택 한도를 확인하지 않는 것.

## 대표 로컬 풀이

- [11266.cpp](./11266.cpp): `visited`와 `up_limit`으로 low-link를 직접 드러낸 현재 폴더의 구현
