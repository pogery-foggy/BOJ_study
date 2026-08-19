#include <iostream>

using namespace std;

int N, dp[1005];
void init() {
    cin >> N;
    dp[1] = dp[3] = dp[4] = 1;
    dp[2] = 0;
}

void solve() {

    for (int i = 5; i <= N; ++i) {
        if (dp[i - 1] == 1 && dp[i - 3] == 1 && dp[i - 4] == 1) {
            dp[i] = 0;
        } else
            dp[i] = 1;
    }

    if (dp[N])
        cout << "SK";
    else
        cout << "CY";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}