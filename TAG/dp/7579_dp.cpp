#include <algorithm>
#include <iostream>
using namespace std;

int N, M;
int dp[101][10001];
int c[101], m[101];
int total;

void init() {
    cin >> N >> M;
    // memory
    for (int i = 1; i <= N; i++) {
        cin >> m[i];
    }
    // cost
    for (int i = 1; i <= N; i++) {
        cin >> c[i];
        total += c[i];
    }
}

void solve() {
    // N * M = 10000
    // 0부터 sum(M)까지
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= total; j++) {
            // 기본 세팅
            if(j == 0) dp[i][j] = dp[i-1][j];
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

            if (j >= c[i])
                dp[i][j] = max(m[i] + dp[i - 1][j - c[i]], dp[i][j]);
        }
    }

    for (int i = 0; i <= total; i++) {
        if (dp[N][i] >= M) {
            cout << i;
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}