#include <iostream>

using namespace std;
int N;
long long dp[91][2];
void init() {
    cin >> N;
    dp[1][0] = 0;
    dp[1][1] = 1;
}

void solve() {
    for (int i = 2; i <= N; i++) {
        dp[i][1] = dp[i - 1][0];
        dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
    }
    cout << dp[N][1] + dp[N][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}