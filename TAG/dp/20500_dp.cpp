#include <iostream>
#define DIV 1000000007
using namespace std;

int N;

long long dp[3][1516];

void init() {
    cin >> N;
    dp[2][1] = 1;
}
// 5부터 시작해야한다.

void solve() {
    for (int i = 2; i <= N; i++) {
        dp[0][i] += dp[1][i - 1] + dp[2][i - 1];
        dp[1][i] += dp[2][i - 1] + dp[0][i - 1];
        dp[2][i] += dp[0][i - 1] + dp[1][i - 1];
        for (int j = 0; j < 3; j++) {
            dp[j][i] %= DIV;
        }
    }
    cout << dp[0][N];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}