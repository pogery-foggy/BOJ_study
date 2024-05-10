#include <cstring>
#include <iostream>
#define MAX_N 16
#define INF 90000000
using namespace std;

int dp[MAX_N][1 << MAX_N];
int W[MAX_N][MAX_N];
int N;

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> W[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));
}

int dfs(int cur, int is_visit) {
    if (is_visit == (1 << N) - 1) {
        if (W[cur][0] == 0)
            return INF;
        return W[cur][0];
    }

    if (dp[cur][is_visit] != -1)
        return dp[cur][is_visit];

    // 탐색을 안했을때는 -1이니까
    dp[cur][is_visit] = INF;

    for (int i = 0; i < N; i++) {
        if (W[cur][i] == 0)
            continue;
        if ((is_visit & (1 << i)) == (1 << i))
            continue;
        dp[cur][is_visit] = min(dp[cur][is_visit], W[cur][i] + dfs(i, is_visit | (1 << i)));
    }
    return dp[cur][is_visit];
}

void solve() { cout << dfs(0, 1); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}