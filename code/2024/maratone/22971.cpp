#include <algorithm>
#include <iostream>
#define DIV 998244353
using namespace std;
int N;
long long arr[5001];
long long dp[5001];
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    dp[1] = 1;
}

void solve() {
    for (int i = 2; i <= N; i++) {
        for (int j = i - 1; j >= 1; j--) {
            if (arr[i] > arr[j]) {
                dp[i] = (dp[i] + dp[j]) % DIV;
            }
        }
        dp[i] = (dp[i] + 1) % DIV;
    }
    for (int i = 1; i <= N; i++) {
        cout << dp[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}