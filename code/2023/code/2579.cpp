#include <iostream>
#define MAX_N 300
using namespace std;

int dp[MAX_N + 1], stair[MAX_N + 1];
int N;

// i-3 -> i-2 -> i, i-3 ->i-1 -> i

void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> stair[i];
    }
    dp[1] = stair[1];
    dp[2] = stair[2] + stair[1]; // max
    dp[3] = max(stair[1] + stair[3], stair[2] + stair[3]);
}

void solve() {
    for (int i = 4; i <= N; i++) {
        dp[i] = max(dp[i - 2], dp[i - 3] + stair[i - 1]) + stair[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << dp[N] << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}