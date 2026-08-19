#include <iostream>
#define DIV 1000000007

using namespace std;

long long dp[1000001];
long long tmxor[1000001];
int N;

void init() {
    cin >> N;
    dp[0] = 0;
    dp[1] = 2;
    dp[2] = 7;
    tmxor[2] = 1;
    // 네번 계속 교차로 오는경우 dp[i-1]*2
    // 세번(2x3) 전에서 *2
    // 두번(2x2) 전에서 12-2, 12-1 11-2, 12-1 11-2 *3개
    // 한번(2x1) 전에서 *2
}

void solve() {
    for (int i = 3; i <= N; i++) {
        tmxor[i] = (tmxor[i - 1] + dp[i - 3]) % DIV;
        dp[i] = ((dp[i - 2] * 3)  + (dp[i - 1] * 2)+ (tmxor[i] * 2)) % DIV;
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