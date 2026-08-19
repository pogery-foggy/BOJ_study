#include <algorithm>
#include <iostream>
using namespace std;
int dp[10001][501][2];
int arr[10001];
int N, M;
void init() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    dp[1][1][1] = arr[1];
    dp[1][0][0] = 0;
}

void solve() {
    for (int i = 2; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            if (j == 1) {
                dp[i][j][1] = dp[i - 1][j - 1][0] + arr[i];
                dp[i][j][0] = max(dp[i - 1][j + 1][1], dp[i - 1][j + 1][0]);
            } else {
                if (j == 0) {
                    dp[i][j][0] = max(dp[i - 1][j + 1][0], dp[i - 1][j + 1][1]);
                    dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][0]);
                } else { // j>=2
                    dp[i][j][1] = dp[i - 1][j - 1][1] + arr[i];
                    dp[i][j][0] = max(dp[i - 1][j + 1][1], dp[i - 1][j + 1][0]);
                }
            }
        }
    }
    cout << dp[N][0][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}