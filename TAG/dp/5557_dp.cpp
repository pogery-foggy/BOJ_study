#include <iostream>

using namespace std;

int arr[100], N, result;
long long dp[101][21];

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    dp[0][arr[0]] = 1;
}

void solve() {
    for (int i = 1; i < N - 1; i++) {
        int temp = arr[i];
        for (int j = 0; j <= 20; j++) {
            if (temp + j < 21) {
                dp[i][j + temp] += dp[i - 1][j];
            }
            if (j - temp >= 0) {
                dp[i][j - temp] += dp[i - 1][j];
            }
        }
    }
    cout << dp[N - 2][arr[N - 1]];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}