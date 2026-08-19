#include <iostream>
#include <vector>
using namespace std;
vector<long long> arr;
long long N, M, K, cnt = 0, total = 0;
void init() {
    total = 0, cnt = 0;
    cin >> N >> M >> K;
    arr.resize(N + M);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < M; i++) {
        arr[N + i] = arr[i];
    }
    for (int i = 0; i < M; i++) {
        total += arr[i];
    }
    if (total < K)
        cnt++;
}

void solve() {
    if (N == M) {
        cout << cnt << "\n";
        return;
    }
    for (int i = 0; i < N - 1; i++) {
        total -= arr[i];
        total += arr[M + i];
        if (total < K) {
            cnt++;
        }
    }
    cout << cnt << "\n";
}

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