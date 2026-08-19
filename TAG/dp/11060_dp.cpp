#include <iostream>
#define DIV 10007
using namespace std;

int N, K;
long long dp[1001][1001];

void init() {
    cin >> N >> K;

    dp[0][0] = 1;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0)
                dp[i][0] = 1;
            else if (j == i)
                dp[i][j] = 1;
            else
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % DIV;
        }
    }
    cout << dp[N][K];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}