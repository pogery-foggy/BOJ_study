#include <iostream>

using namespace std;
int N, M;
void init() { cin >> N; }

void solve() {
    long long dp[21][10001] = {0};
    int coin[21];
    for (int i = 1; i <= N; i++) {
        cin >> coin[i];
        dp[i][0] = 1; // 사용 안하는 방법
    }
    cin >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            dp[i][j] = dp[i - 1][j];            // 복사해놓고
            if (j >= coin[i])                   // 만약 더 만들 수 있었으면
                dp[i][j] += dp[i][j - coin[i]]; // 이번 동전으로 만드는 방법
        }
    }
    cout << dp[N][M]<<"\n";
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