#include <iostream>
#define MAX_N 10000
using namespace std;

long long dp[MAX_N + 1];
int N;

void init() {
    cin >> N;
    dp[0] = 0;
    dp[1] = 1;
}

void solve() {
    for (int i = 2; i <= N; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << dp[N];
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}