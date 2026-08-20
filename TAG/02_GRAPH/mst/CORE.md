# 최소 신장 트리(MST) 핵심 복원 노트

## 한 문장 기억

**가장 싼 간선부터 보면서 서로 다른 연결 요소를 잇는 간선만 받아들이면, 사이클 없이 모든 정점을 잇는 최소 비용 트리가 된다.**

## 언제 꺼내는가

- 모든 정점을 연결하는 총비용을 최소화한다.
- 도로·케이블·파이프 설치에서 연결만 중요하고 경로별 최단 거리는 중요하지 않다.
- 완전 그래프의 간선이 너무 많으면 문제의 비용 구조로 MST 후보 간선을 줄일 수 있다.

## 핵심 상태와 불변식

- 선택된 간선은 항상 사이클 없는 숲이다.
- DSU의 서로 다른 대표를 잇는 간선만 선택한다.
- 비용 오름차순으로 본 첫 유효 간선은 현재 컷을 잇는 안전한 간선이다.
- 정점이 `N`개면 정확히 `N-1`개를 선택했을 때 완성된다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [1922.cpp](./1922.cpp)의 `priority_queue<pair<int, pair<int, int>>>`, 비용을 음수로 넣는 최소 힙 처리, 전역 부모 배열 `p`, `find_parent()`/`union_find()` 함수명과 `cnt`/`total_cost` 흐름을 보존했다.

```cpp
priority_queue<pair<int, pair<int, int>>> pq;
int N, M, p[1001];

void init() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        pq.push({-c, {u, v}});
    }
    for (int i = 1; i <= N; i++)
        p[i] = i;
}

int find_parent(int x) {
    if (p[x] == x) return x;
    return p[x] = find_parent(p[x]);
}

void union_find(int a, int b) {
    a = find_parent(a);
    b = find_parent(b);
    if (a == b) return;
    p[a] = b;
}

void solve() {
    int cnt = 0;
    int total_cost = 0;
    while (!pq.empty() && cnt < N - 1) {
        int c = -pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();
        if (find_parent(u) == find_parent(v)) continue;
        total_cost += c;
        union_find(u, v);
        cnt++;
    }
    if (cnt == N - 1) cout << total_cost;
}
```

원본 문제는 연결 그래프를 보장하지만, 재사용 골격에서는 `pq.empty()`도 함께 검사해 빈 힙 접근을 막았다.

## 빈 화면 구현 순서

1. 목표가 최단 경로가 아니라 “전체 연결 최소 비용”인지 확인한다.
2. 모든 정점의 DSU 부모를 자기 자신으로 초기화한다.
3. 간선을 비용 오름차순으로 정렬하거나 최소 힙에 넣는다.
4. 양 끝의 대표가 다를 때만 합치고 비용/간선 수를 갱신한다.
5. `N-1`개를 선택하면 종료한다.
6. 끝까지 `N-1`개가 안 되면 비연결 그래프 처리를 한다.
7. 간선 수가 너무 크면 안전한 후보 간선 생성 규칙을 먼저 증명한다.

## 자주 틀리는 지점

- DSU를 초기화하지 않거나, 선택 뒤 union을 빼먹는 것.
- 우선순위 큐의 최소/최대 방향을 뒤집는 것.
- 비용 합을 `int`에 담는 것.
- 그래프가 연결되지 않았는데 힙이 빌 때까지 `top()`을 호출하는 것.
- [2887.cpp](./2887.cpp) 같은 후보 축소에서 정렬 후 원래 정점 ID를 잃는 것.
- DSU는 도구일 뿐, “왜 이 후보 간선만으로 MST가 보존되는가”가 주 알고리즘인 문제를 놓치는 것.

## 대표 로컬 풀이

- [1922.cpp](./1922.cpp): 우선순위 큐와 DSU를 이용한 Kruskal 기본형
- [2887.cpp](./2887.cpp): 좌표별 인접 정점만 남겨 간선 수를 줄인 핵심 응용
- [17472.cpp](./17472.cpp): 섬 라벨링·다리 생성 뒤 MST
- [4792.cpp](./4792.cpp): 간선 정렬 순서를 바꿔 가능한 색 간선 수 범위를 판정
