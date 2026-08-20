# 0-1 BFS 핵심 복원 노트

## 한 문장 기억

**간선 비용이 0이면 deque 앞, 1이면 뒤에 넣어 아직 처리할 상태를 거리 순으로 유지하는 다익스트라 특수형이다.**

## 언제 꺼내는가

- 모든 간선 비용이 정확히 0 또는 1이다.
- 단순 BFS는 비용 차이를 표현하지 못하고, 일반 다익스트라보다 deque가 간결하다.
- 순간이동 0·걷기 1, 빈칸 0·벽 부수기 1 같은 모델이다.

## 핵심 상태와 불변식

- `dist[v]`: 현재까지 발견한 최소 비용이며, 더 작은 값이 생기면 다시 갱신할 수 있다.
- 비용 0으로 완화한 정점은 `push_front`, 비용 1은 `push_back`한다.
- deque 앞쪽에는 현재 최소 거리 후보가 온다.
- 일반적인 안전한 구현은 단순 `visited`가 아니라 거리 비교 `nd < dist[v]`를 쓴다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [1261.cpp](./1261.cpp)의 전역 `map`/방향 배열, `is_valid()`/`bfs()`/`solve()` 분리, `deque<pair<int, int>>`와 `front().first`/`second` 좌표 처리 방식을 보존했다. 원본의 한 번 방문 방식은 더 짧은 경로 재갱신을 막을 수 있어 `dist` 완화로 바로잡았다.

```cpp
#define INF 1000000000

int N, M;
int map[101][101];
int dist[101][101];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool is_valid(int x, int y) {
    if (x < 0 || x >= M) return false;
    if (y < 0 || y >= N) return false;
    return true;
}

int bfs(int y, int x) {
    deque<pair<int, int>> dq;
    dq.push_front({y, x});
    dist[y][x] = 0;

    while (!dq.empty()) {
        int y = dq.front().first;
        int x = dq.front().second;
        dq.pop_front();

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (!is_valid(nx, ny)) continue;

            int next_dist = dist[y][x] + map[ny][nx];
            if (dist[ny][nx] <= next_dist) continue;
            dist[ny][nx] = next_dist;
            if (map[ny][nx] == 0)
                dq.push_front({ny, nx});
            else
                dq.push_back({ny, nx});
        }
    }
    return dist[N - 1][M - 1];
}
```

`bfs()` 전에 `dist[i][j] = INF`로 전 범위를 초기화해야 한다. 오류 가능성이 있는 방문 로직만 교정했고, 좌표·배열·함수 스타일은 원본을 유지했다.

## 빈 화면 구현 순서

1. 이동 비용이 정말 0/1뿐인지 확인한다.
2. `dist`를 `INF`, 시작점을 0으로 둔다.
3. deque 앞에서 상태를 꺼낸다.
4. 모든 이웃에 대해 `nd=dist[cur]+w`를 계산한다.
5. 더 짧을 때만 거리를 갱신한다.
6. `w==0`이면 앞, `w==1`이면 뒤에 넣는다.
7. 목표 조기 종료는 “꺼낸 값이 최신 최단 거리”임을 보장할 때만 한다.

## 자주 틀리는 지점

- 비용 0과 1의 `push_front`/`push_back`을 반대로 쓰는 것.
- 처음 큐에 넣은 순간 영구 방문 처리해 나중의 더 싼 0비용 경로를 막는 것.
- 시작 거리를 1로 두고 마지막에 빼는 관습 때문에 다른 코드와 섞을 때 오류가 나는 것.
- 일반 가중치가 섞였는데 0-1 BFS를 사용하는 것.
- `x/y`, `N/M` 범위를 뒤바꾸는 것.

## 대표 로컬 풀이

- [1261.cpp](./1261.cpp): 빈칸은 앞, 벽은 뒤에 넣는 격자형 발상 확인용. 다만 재학습 시에는 위처럼 거리 완화로 구현하는 편이 안전함
- [13549.cpp](./13549.cpp): 순간이동 0, 걷기 1의 정점 그래프형 0-1 BFS
