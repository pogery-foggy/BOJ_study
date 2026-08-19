#include <algorithm>
#include <iostream>
using namespace std;
int arr[5001], answer, N;
int dp[5001][5001];
void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
}

int fnd(int s, int e) {
    if (dp[s][e])
        return dp[s][e];
    if (s == e)
        return 0;
    if (e - s == 1 && arr[s] == arr[e])
        return 0;
    if (arr[s] == arr[e])
        return dp[s][e] = fnd(s + 1, e - 1);
    return dp[s][e] = min(fnd(s, e - 1) + 1, fnd(s + 1, e) + 1);
}

void solve() {
    answer = fnd(0, N - 1);
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}