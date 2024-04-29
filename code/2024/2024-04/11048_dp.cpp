#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int map[1001][1001];
int dp[1001][1001];
bool is_visit[1001][1001];
int N, M;
queue<pair<int, int>> q;
int dx[] = {1, 0};
int dy[] = {0, 1};

void init() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> map[i][j];
        }
    }
    dp[0][0] = map[0][0];
    for (int i = 1; i <= M; i++) {
        dp[1][i] = dp[1][i - 1] + map[0][i];
    }
}

void solve() {

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            dp[i][j] += map[i][j];
        }
    }

    cout << dp[N][M];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}