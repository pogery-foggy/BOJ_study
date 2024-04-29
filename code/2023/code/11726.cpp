#include <iostream>
#define MOD 10007
using namespace std;

int dp[1001], N;

void init() {
    cin >> N;
    dp[1] = 1;
    dp[2] = 2;
}

void solve() {
    for (int i = 3; i <= N; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
        dp[i] %= MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << dp[N];
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}