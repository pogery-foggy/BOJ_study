#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int N, K;
int arr[300000];
vector<int> cost;
void init() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i < N; i++) {
        cost.push_back(arr[i] - arr[i - 1]);
    }
    sort(cost.begin(),cost.end());
}

void solve() {
    long long answer = 0;
    for(int i = 0; i<N-K;i++){
        answer += cost[i];
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