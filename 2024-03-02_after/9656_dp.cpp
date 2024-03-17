#include <iostream>

using namespace std;

int dp[1001], N;

void init() {
    cin >> N;
    dp[0] = 1;
    dp[1] = 0;
    dp[2] = 1;
}

void solve() {
    for (int i = 3; i <= N; i++) {
        if ((!dp[i - 1]) || (!dp[i - 3]))
            dp[i] = 1;
    }
    cout << (dp[N] ? "SK" : "CY");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}