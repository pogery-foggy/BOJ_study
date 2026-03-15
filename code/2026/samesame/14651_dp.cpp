#include <iostream>
#define DIV 1000000009
#define MAX_N 33334
using namespace std;
int N;
long long dp[MAX_N][3];
void init() {
    // 합 0
    // 합 1
    // 합 2
    cin >> N;
    dp[1][0] = 0;
    dp[1][1] = 1;
    dp[1][2] = 1;
}

void solve() {
    if(N == 1) {
        cout << 0;
        return;
    }
    for(int i = 2; i <= N; i++){
        dp[i][0] = (dp[i-1][0] + dp[i-1][1] + dp[i-1][2]) % DIV;
        dp[i][1] = (dp[i-1][0] + dp[i-1][1] + dp[i-1][2]) % DIV;
        dp[i][2] = (dp[i-1][0] + dp[i-1][1] + dp[i-1][2]) % DIV;
    }
    cout << dp[N][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}