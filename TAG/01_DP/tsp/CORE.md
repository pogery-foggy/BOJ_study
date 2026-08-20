# TSP 비트마스크 DP 핵심 복원 노트

## 한 문장 기억

**현재 도시와 방문 집합이 같으면 앞으로 필요한 최소 비용도 같으므로 `dp[cur][mask]`로 한 번만 계산한다.**

## 언제 꺼내는가

- 모든 정점/대상을 정확히 한 번씩 방문해야 한다.
- `N`이 대략 16~20 이하라 `2^N` 상태를 감당할 수 있다.
- 방문 순서의 완전탐색 `N!`을 방문 집합이 같은 경우끼리 합칠 수 있다.

## 핵심 상태와 불변식

- `dp[cur][mask]`: 현재 `cur`, 이미 방문한 집합 `mask`에서 출발점으로 돌아가기까지의 최소 추가 비용.
- `mask`에는 반드시 `cur`와 시작점이 포함된다.
- 모두 방문했을 때 `cur -> start` 간선이 없으면 `INF`다.
- 방문하지 않은 `next`만 골라 `cost[cur][next] + dfs(next, mask | 1<<next)`로 전이한다.

## C++ 최소 구현 골격

[2098.cpp](./2098.cpp)의 메모이제이션 DFS 구조다.

```cpp
const int INF = 1e9;
vector<vector<int>> memo(n, vector<int>(1 << n, -1));

int dfs(int cur, int mask) {
    if (mask == (1 << n) - 1)
        return w[cur][0] ? w[cur][0] : INF;

    int &ret = memo[cur][mask];
    if (ret != -1) return ret;
    ret = INF;

    for (int next = 0; next < n; ++next) {
        if (mask & (1 << next)) continue;
        if (w[cur][next] == 0) continue;
        ret = min(ret, w[cur][next] + dfs(next, mask | (1 << next)));
    }
    return ret;
}

cout << dfs(0, 1 << 0);
```

## 빈 화면 구현 순서

1. 회전 대칭이므로 시작점을 0으로 고정한다.
2. `mask`의 비트가 1이면 방문 완료라고 정한다.
3. 모든 방문 상태의 귀환 비용을 기저로 쓴다.
4. `memo`를 미계산 값 `-1`로 초기화한다.
5. 미방문이며 존재하는 간선만 순회해 최솟값을 갱신한다.
6. `INF + 비용`이 넘치지 않도록 상수와 자료형을 확인한다.

## 자주 틀리는 지점

- `0`이 실제 비용인지 “간선 없음”인지 문제 정의를 확인하지 않는 것.
- 시작점을 mask에 넣지 않는 것.
- 마지막 도시에서 시작점으로 돌아갈 수 없는 경우를 0으로 처리하는 것.
- 배열 크기를 `[1<<N][N]`과 `[N][1<<N]` 사이에서 잘못 잡는 것.
- `1 << N`에서 `N`이 자료형 비트 수에 가까운데 `int`를 쓰는 것.

## 대표 로컬 풀이

- [2098.cpp](./2098.cpp): 현재 폴더의 유일한 풀이이며, `dfs(cur, visited)` 메모이제이션 정석 구현
