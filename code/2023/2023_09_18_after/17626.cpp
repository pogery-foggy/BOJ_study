#include <iostream>

using namespace std;

int N, dp[50001];
void init() {
    cin >> N;
    dp[1] = 1;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        dp[i] = dp[1] + dp[i - 1];
        for (int j = 2; j * j <= i; j++)
            dp[i] = min(dp[i], 1 + dp[i - j * j]);
    }
    cout << dp[N];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}