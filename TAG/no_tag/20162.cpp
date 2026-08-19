#include <algorithm>
#include <iostream>
using namespace std;
int N;
int arr[1001];
int dp[1001];
int total[1001];
int answer;
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
}

void solve() {
    for (int i = 1; i <= N; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (arr[j] < arr[i]) {
                total[i] = max(total[i], total[j] + arr[i]);
                answer = max(answer, total[i]);
            }
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