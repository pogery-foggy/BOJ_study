#include <iostream>
#define DIV 9901 
using namespace std;

int dp[100001][3], N;

void init() {
    cin >> N;
    dp[1][0] = 1;
    dp[1][1] = 1;
    dp[1][2] = 1;
}

void solve() {
    for (int i = 2; i <= N; i++) {
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % DIV;
        dp[i][1] = (dp[i - 1][2] + dp[i - 1][0]) % DIV;
        dp[i][2] = (dp[i - 1][1] + dp[i - 1][0]) % DIV;
    }
    cout << (dp[N][0] + dp[N][1] + dp[N][2]) % DIV;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();

    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}