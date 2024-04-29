#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;

int arr[1001][4];
int dp[1001][4];
int N;
// 5 4 3
pair<int, int> idx[6] = {{0, 0}, {0, 0}, {0, 0}, {1, 2}, {1, 3}, {2, 3}};
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= 3; j++) {
            cin >> arr[i][j];
        }
    }
    dp[1][1] = arr[1][1];
    dp[1][2] = arr[1][2];
    dp[1][3] = arr[1][3];
}

void solve() {
    for (int i = 2; i <= N; i++) {
        for (int j = 1; j <= 3; j++) {
            dp[i][j] = min(dp[i - 1][idx[6 - j].first], dp[i - 1][idx[6 - j].second]);
            dp[i][j] += arr[i][j];
        }
    }

    cout << min({dp[N][1],dp[N][2],dp[N][3]});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}