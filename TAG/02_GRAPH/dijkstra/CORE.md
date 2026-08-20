# 다익스트라 핵심 복원 노트

## 한 문장 기억

**음수가 없는 간선에서 현재까지 가장 가까운 정점을 우선 꺼내고, 그 정점을 거쳐 더 짧아지는 이웃만 갱신한다.**

## 언제 꺼내는가

- 가중치가 0 이상인 그래프의 단일 시작점 최단 거리를 구한다.
- 특정 경유지를 거치는 거리, 왕복 거리, 격자 비용을 여러 번 조합한다.
- 간선 비용이 0/1만이면 `zero_one_bfs`, 모든 쌍이면 Floyd–Warshall도 비교한다.

## 핵심 상태와 불변식

- `dist[v]`: 지금까지 발견한 시작점→`v` 경로 중 최소 비용.
- 최소 힙에는 `(발견 당시 거리, 정점)`을 넣는다.
- 꺼낸 거리 `d`가 현재 `dist[u]`와 다르면 낡은 항목이므로 버린다.
- 음수 간선이 없을 때 최소 거리 순서가 깨지지 않는다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [1753.cpp](./1753.cpp)의 `INF` 매크로, 전역 `edge`와 `dist`, `pair<int, int>` 최소 힙, `cur`/`distance`/`next_dist` 변수명, `dijkstra()`와 `solve()` 함수 분리를 그대로 축약했다.

```cpp
#define INF 2100000000

vector<pair<int, int>> edge[20001];
vector<int> dist(20001, INF);
int N, M, s;

void dijkstra() {
    dist[s] = 0;
    priority_queue<pair<int, int>,
        vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({dist[s], s});

    while (!pq.empty()) {
        int cur = pq.top().second;
        int distance = pq.top().first;
        pq.pop();
        if (distance > dist[cur])
            continue;

        for (auto next : edge[cur]) {
            int next_dist = next.second + distance;
            if (dist[next.first] > next_dist) {
                dist[next.first] = next_dist;
                pq.push({next_dist, next.first});
            }
        }
    }
}

void solve() { dijkstra(); }
```

## 빈 화면 구현 순서

1. 간선 방향과 가중치가 음수 아닌지 확인한다.
2. 인접 리스트에 `(도착점, 비용)`을 저장한다.
3. 거리를 `INF`, 시작점만 0으로 둔다.
4. 최소 힙에서 `(거리, 정점)`을 꺼낸다.
5. 낡은 큐 항목을 건너뛴다.
6. 모든 이웃을 완화하고 줄었을 때만 힙에 넣는다.
7. 경로가 필요하면 갱신 시 `parent[v]=u`를 기록한다.

## 자주 틀리는 지점

- C++ 기본 `priority_queue`가 최대 힙임을 잊는 것.
- 음수 간선에 그대로 사용하는 것.
- 낡은 항목 제거를 빼 성능이 나빠지는 것.
- 거리 합을 `int`로 두거나 `INF`에 값을 더해 넘치는 것.
- 무방향 간선을 한 방향만 넣는 것.
- 여러 번 실행할 때 `dist`와 큐를 초기화하지 않는 것.

## 대표 로컬 풀이

- [1753.cpp](./1753.cpp): 단일 시작점 다익스트라의 기본형
- [1504.cpp](./1504.cpp): 여러 다익스트라 결과로 필수 경유 순서를 비교
- [1238.cpp](./1238.cpp): 왕복 최단 거리 구성
- [13907.cpp](./13907.cpp): 간선 수를 상태에 더한 DP 결합형
