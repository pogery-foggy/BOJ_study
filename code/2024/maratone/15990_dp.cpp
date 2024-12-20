#include <iostream>
#define DIV 1000000009L
using namespace std;

long long dp[100001][4];

void init() {
    dp[0][1] = dp[0][2] = dp[0][3] = dp[1][2] = dp[1][3] = dp[2][1] = dp[2][3] = 0;
    dp[1][1] = 1;                       // 1
    dp[2][2] = 1;                       // 2
    dp[3][1] = dp[3][2] = dp[3][3] = 1; // 12 21 3
    for (int i = 4; i <= 100000; i++) {
        dp[i][1] = (dp[i - 1][2] + dp[i - 1][3]) % DIV;
        dp[i][2] = (dp[i - 2][1] + dp[i - 2][3]) % DIV;
        dp[i][3] = (dp[i - 3][1] + dp[i - 3][2]) % DIV;
    }
}

void solve() {
    int a;
    cin >> a;
    cout << (dp[a][1] + dp[a][2] + dp[a][3]) % DIV << "\n";
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