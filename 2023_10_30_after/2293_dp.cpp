#include <iostream>

using namespace std;

int n, k;
int dp[10001];
int coin[101];
void init() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> coin[i];
    }
    dp[0] = 1;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = coin[i]; j <= k; j++) {
            dp[j] += dp[j - coin[i]];
        }
    }
    cout << dp[k];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}