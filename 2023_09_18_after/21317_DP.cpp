#include <iostream>
#include <vector>

using namespace std;

int N, dp[21][2], K;
vector<pair<int, int>> arr;

void init() {
    cin >> N;
    arr.resize(N);
    for (int i = 1; i < N; i++) {
        int small, big;
        cin >> small >> big;
        arr[i] = make_pair(small, big);
    }
    cin >> K;
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 2; j++) {
            dp[i][j] = 500000;
        }
    }
}

void solve() {
    dp[1][0] = 0;
    dp[2][0] = arr[1].first;
    dp[3][0] = min(arr[1].first + arr[2].first, arr[1].second);

    for (int i = 4; i < N + 1; i++) {
        dp[i][0] = min(arr[i - 1].first + dp[i - 1][0], arr[i - 2].second + dp[i - 2][0]);
        dp[i][1] = min(K + dp[i - 3][0], min(arr[i - 1].first + dp[i - 1][1], arr[i - 2].second + dp[i - 2][1]));
    }
    cout << min(dp[N][0], dp[N][1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}