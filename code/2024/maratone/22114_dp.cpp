#include <iostream>

using namespace std;
int arr[100001];
int dp[100001][2]; // x o
int N, K;
void init() {
    cin >> N >> K;
    N--;
    arr[0] = 0;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    dp[0][0] = 1;
    dp[0][1] = 1;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        if (arr[i] > K) {
            dp[i][0] = 1;
            dp[i][1] = dp[i - 1][0] + 1;
        } else {
            dp[i][0] = dp[i - 1][0] + 1;
            dp[i][1] = dp[i - 1][1] + 1;
        }
    }
    int maxi = 0;
    for (int i = 0; i <= N; i++) {
        maxi = maxi > dp[i][1] ? maxi : dp[i][1];
    }
    cout << maxi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}