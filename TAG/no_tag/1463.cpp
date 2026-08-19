#include <iostream>
#define MAX_N 1000000
using namespace std;
int dp[MAX_N], N;

void init() {
    cin >> N;
    for (int i = 2; i <= N; i++)
        dp[i] = N + 1;
}

void solve() {
    for (int i = 2; i <= N; i++) {
        dp[i] = min(dp[i], dp[i - 1] + 1);
        if (!(i % 2))
            dp[i] = min(dp[i], dp[i >> 1] + 1);
        if (!(i % 3))
            dp[i] = min(dp[i], dp[i / 3] + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << dp[N] << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}