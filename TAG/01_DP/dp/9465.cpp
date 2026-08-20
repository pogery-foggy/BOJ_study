#include <iostream>
#include <algorithm>
#define MAX_N 100001
using namespace std;

int arr[MAX_N][2], N;
int dp[MAX_N][2];
void init() {
    cin >> N;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[j][i];
        }
    }
    dp[0][0] = arr[0][0];
    dp[0][1] = arr[0][1];
    dp[1][0] = arr[0][1] + arr[1][0];
    dp[1][1] = arr[0][0] + arr[1][1];
}


void solve() {
    for (int i = 2; i < N; i++) {
        dp[i][0] = max(dp[i - 1][1] + arr[i][0], dp[i - 2][1] + arr[i][0]);
        dp[i][1] = max(dp[i - 1][0] + arr[i][1], dp[i - 2][0] + arr[i][1]);
    }
    cout << max(dp[N - 1][0], dp[N - 1][1]) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}