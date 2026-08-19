#include <iostream>

using namespace std;

int N;
long long dp[36];

void init() {
    cin >> N;
    dp[0] = 1;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        long long sum = 0;
        for (int j = 0; j < i; j++) {
            sum += dp[j] * dp[i - j - 1];
        }
        dp[i] = sum;
    }
    cout << dp[N];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}