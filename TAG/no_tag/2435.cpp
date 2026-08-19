#include <iostream>

using namespace std;
int N, K, arr[101];
int maxi = -999999999, total;
void init() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
}

void solve() {
    for (int i = 0; i < N - K + 1; i++) {
        total = 0;
        for (int j = i; j < i + K; j++) {
            total += arr[j];
        }
        maxi = maxi > total ? maxi : total;
    }
    cout << maxi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}