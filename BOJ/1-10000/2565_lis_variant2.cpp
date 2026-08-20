#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
vector<pair<int, int>> arr;
int dp[501];
int answer = 1;

void init() {
    cin >> N;
    arr.resize(N);
    for (auto& a : arr) {
        cin >> a.first >> a.second;
    }
    sort(arr.begin(), arr.end());
}

void solve() {
    for (int i = 0; i < N; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i].second > arr[j].second) {
                dp[i] = max(dp[i], dp[j] + 1);
                answer = max(dp[i], answer);
            }
        }
    }
    cout << N - answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}