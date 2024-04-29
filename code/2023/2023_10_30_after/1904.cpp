#include <iostream>
#define DIV 15746
using namespace std;

long long dp[1000001];
int N;
void init() {
    cin >> N;
    dp[1] = 1;
    dp[2] = 2;
}
// 2
// 00 1
//  100 111 001
void solve() {
    for (int i = 3; i <= N; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
        dp[i] %= DIV;
    }
    cout << dp[N];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}