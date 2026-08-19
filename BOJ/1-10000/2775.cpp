#include <iostream>

using namespace std;

int dp[15][14];

void init() {
    for (int i = 0; i < 14; i++) {
        dp[0][i] = i + 1;
    }
    for (int i = 0; i < 15; i++) {
        dp[i][0] = 1;
    }
    for (int i = 1; i < 15; i++) {
        for (int j = 1; j < 14; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
}

void solve() {
    int n, k;
    cin >> k >> n;
    cout << dp[k][n - 1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    init();
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}