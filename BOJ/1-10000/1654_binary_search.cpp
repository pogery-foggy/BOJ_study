#include <iostream>
#define MAX_N 10000
using namespace std;

int K, k_arr[MAX_N], max_stick = -1, N, rotn, answer;
long long mid, l, r;

void init() {
    cin >> K >> N;
    for (int i = 0; i < K; i++) {
        cin >> k_arr[i];
        max_stick = max_stick > k_arr[i] ? max_stick : k_arr[i];
    }
    l = 1;
    r = max_stick;
}

void solve() {

    while (l <= r) {
        mid = (l + r) >> 1;
        rotn = 0;
        for (int i = 0; i < K; i++) {
            rotn += k_arr[i] / mid;
        }
        if (rotn >= N) {
            l = mid + 1;
            answer = mid > answer ? mid : answer;
        } else
            r = mid - 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << answer;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}