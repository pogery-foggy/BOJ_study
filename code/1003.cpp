#include <iostream>
#include <vector>
using namespace std;

pair<int, int> dp[41];
int N;
void solve() {
    dp[0] = {1, 0};
    dp[1] = {0, 1};
    for (int i = 2; i <= N; i++) {
        dp[i] = {dp[i-1].first + dp[i-2].first, dp[i-1].second + dp[i-2].second};
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N;
        solve();
        cout << dp[N].first << " " << dp[N].second << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}