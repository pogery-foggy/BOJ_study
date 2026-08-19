#include <iostream>
#define DIV 1000000000
using namespace std;

long long dp[101][10];
int N;
void init() {
    cin >> N;
    for (int i = 1; i < 10; i++) {
        dp[1][i] = 1;
    }
}

void solve() {
    for (int i = 2; i <= N; i++) {
        for (int j = 0; j < 10; j++) {
            if (j > 0)
                dp[i][j] += dp[i - 1][j - 1];
            if (j < 9)
                dp[i][j] += dp[i - 1][j + 1];
            dp[i][j] %= DIV;
        }
    }
    long long answer = 0;
    for (int i = 0; i < 10; i++) {
        answer += dp[N][i];
    }
    answer %= DIV;
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}