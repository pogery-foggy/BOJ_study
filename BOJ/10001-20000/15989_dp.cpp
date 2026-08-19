#include <iostream>

using namespace std;

int N;
long long dp[10001][4];
void init() {
    dp[1][1] = 1;
    dp[2][1] = 1;
    dp[2][2] = 1;
    dp[3][1] = 1;
    dp[3][2] = 1;
    dp[3][3] = 1;
    // 1 로 이루어진거에서 1 더하기
    for (int i = 4; i <= 10000; i++) {
        dp[i][1] += dp[i - 1][1];
        dp[i][2] += dp[i - 2][2] + dp[i - 2][1];
        dp[i][3] += dp[i - 3][3] + dp[i - 3][2] + dp[i - 3][1];
    }
}

void solve() {
    int N;
    cin >> N;
    cout << dp[N][1] + dp[N][2] + dp[N][3] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    init();
    for (int testcase = 0; testcase < T; testcase++) {
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}