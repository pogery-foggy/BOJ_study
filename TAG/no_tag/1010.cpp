#include <iostream>

using namespace std;

long long dp[31][31];
int N, M;
void init() { cin >> N >> M; }

long long fnd(int n, int r) {
    if (n == r || r == 0)
        return 1;
    if (dp[n][r])
        return dp[n][r];

    dp[n][r] = fnd(n - 1, r - 1) + fnd(n - 1, r);
    return dp[n][r];
}

void solve() { cout << fnd(M, N) << "\n"; }

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