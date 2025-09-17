#include <iostream>
#define MOD 10007
using namespace std;

int N, answer;
int poker[53][53];
void init() {
    cin >> N;

    for (int i = 0; i < 53; i++)
        poker[i][0] = 1;
    for (int i = 1; i < 53; i++) {
        for (int j = 1; j < 53; j++) {
            poker[i][j] = poker[i - 1][j] + poker[i - 1][j - 1];
            poker[i][j] %= MOD;
        }
    }
}

void solve() {
    for (int i = 1; i * 4 <= N; i++) {
        if (i % 2 == 1) {
            answer += poker[13][i] * poker[52 - (4 * i)][N - (4 * i)];
            answer %= MOD;
        } else {
            answer -= (poker[13][i] * poker[52 - (4 * i)][N - (4 * i)]) % MOD;
            answer = (answer + MOD) % MOD;
        }
    }
    cout << answer;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}