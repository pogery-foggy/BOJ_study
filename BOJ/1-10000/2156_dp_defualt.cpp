#include <iostream>
#include <algorithm>
using namespace std;
int dp[10001];
int arr[10001], N;
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    dp[0] = 0;
    dp[1] = arr[1];
    if (N >= 2)
        dp[2] = arr[1] + arr[2];
    arr[0] = 0;
}
//1+2 ,2+3, 1+3
void solve() {
    for(int i = 3; i <=N; i++){
        dp[i] = max({dp[i-3]+arr[i-1]+arr[i], dp[i-2]+arr[i], dp[i-1]});
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