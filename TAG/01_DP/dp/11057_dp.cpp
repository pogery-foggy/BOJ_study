#include <iostream>
#define DIV 10007
using namespace std;
int N;
int dp[10][1001];
void init() {
    cin >> N;
    for (int i = 0; i <= 9; i++) {
        dp[i][1] = 1;
    }
}

void solve() {
    for (int i = 2; i <= N; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= j; k++) {
                dp[j][i] += dp[k][i-1];
                dp[j][i] %= DIV;
            }
        }
    }
    int sum = 0;
    for (int i = 0; i <= 9; i++) {
        sum += dp[i][N];
    }
    cout << sum % DIV;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}