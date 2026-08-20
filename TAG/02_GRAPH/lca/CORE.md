# LCA(최소 공통 조상) 핵심 복원 노트

## 한 문장 기억

**두 정점의 깊이를 먼저 맞춘 뒤 부모를 함께 올리면 처음 만나는 정점이 최소 공통 조상이다.**

## 언제 꺼내는가

- 루트 트리에서 두 정점의 가장 가까운 공통 조상을 묻는다.
- 두 정점 사이 거리, 경로상의 정보, 조상 관계 판정의 기반이 필요하다.
- 질의가 적으면 한 칸씩, 많으면 `2^k`번째 조상을 미리 계산한다.

## 핵심 상태와 불변식

- 전처리 DFS/BFS 뒤 `parent[v]`는 바로 위 부모, `depth[v]`는 루트에서의 깊이다.
- 깊이를 맞춘 뒤에는 두 정점이 LCA까지 올라가야 할 간선 수가 같다.
- 한 칸 방식은 `O(높이)`, binary lifting은 전처리 `O(N log N)`·질의 `O(log N)`이다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [11437.cpp](./11437.cpp)의 전역 `p`/`depth`/`edges`, 재귀 `dfs()`로 깊이와 부모를 동시에 만드는 방식, 임시 변수로 두 정점을 바꾸고 한 칸씩 올리는 `solve()` 흐름을 보존했다.

```cpp
#define MAX_N 50001

int p[MAX_N], depth[MAX_N], N;
vector<int> edges[MAX_N];

void dfs(int cur) {
    for (auto next : edges[cur]) {
        if (depth[next] != -1)
            continue;
        depth[next] = depth[cur] + 1;
        p[next] = cur;
        dfs(next);
    }
}

void init() {
    cin >> N;
    for (int i = 1; i <= N; i++)
        depth[i] = -1;
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    depth[1] = 0;
    dfs(1);
}

void solve() {
    int a, b;
    cin >> a >> b;
    if (depth[a] < depth[b]) {
        int temp = a;
        a = b;
        b = temp;
    }
    while (depth[a] != depth[b])
        a = p[a];
    while (a != b) {
        a = p[a];
        b = p[b];
    }
    cout << a << "\n";
}
```

이 골격은 실제 풀이와 같은 한 칸 상승 방식이다. 질의가 많다면 `up[k][v] = up[k-1][up[k-1][v]]`를 만든 뒤 깊이 차와 두 정점을 큰 비트부터 올린다.

## 빈 화면 구현 순서

1. 입력이 무방향 트리인지 부모가 주어진 트리인지 확인한다.
2. 루트를 정하고 부모·깊이를 DFS/BFS로 만든다.
3. 더 깊은 정점을 올려 깊이를 맞춘다.
4. 같지 않으면 두 정점을 동시에 올린다.
5. 질의 수와 트리 높이를 보고 binary lifting 필요 여부를 결정한다.
6. 거리 문제면 `dist[a]+dist[b]-2*dist[lca]`를 사용한다.

## 자주 틀리는 지점

- 루트의 부모/깊이를 초기화하지 않는 것.
- 무방향 트리에서 부모로 되돌아가는 간선을 막지 않는 것.
- 사슬 트리에서 단순 상승이 질의마다 `O(N)`임을 놓치는 것.
- 사슬처럼 깊은 트리를 재귀 `dfs()`로 전처리할 때 호출 스택 한도를 확인하지 않는 것. 필요하면 큐/명시적 스택으로 부모·깊이를 만든다.
- binary lifting의 `LOG`, 테이블 구축 순서, 깊이 차 비트 처리를 틀리는 것.
- 여러 테스트에서 인접 리스트와 깊이를 초기화하지 않는 것.

## 대표 로컬 풀이

- [11437.cpp](./11437.cpp): DFS로 부모·깊이를 만든 뒤 한 칸씩 올리는 기본 구현
- [3584.cpp](./3584.cpp): 부모가 직접 주어지는 작은 LCA 변형
