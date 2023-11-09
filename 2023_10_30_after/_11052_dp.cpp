// kanpsack으로 풀 수는 없을까?
#include <iostream>

using namespace std;
int N;
long long dp[1001];
long long arr[1001];
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    dp[1] = arr[1];
}

void solve() {
    for (int i = 2; i <= N; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i] = dp[i] > dp[i - j] + arr[j] ? dp[i] : dp[i - j] + arr[j];
        }
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