#include <iostream>
#define DIV 1000000000
using namespace std;

int N, K;

long long dp[5001][5001];

void init() {
    cin >> N >> K;
    for (int i = 1; i <= 5000; i++) {
        dp[1][i] = i;
        dp[i][1] = 1;
    }
}

void solve() {
    for (int i = 2; i <= 5000; i++) {
        for (int j = 2; j <= K; j++) {
            dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % DIV;
        }
    }
    cout << dp[N][K];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0;
}