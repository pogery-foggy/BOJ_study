#include <iostream>

using namespace std;
long long N, M, pre, suf, cur, cnt;
long long arr[10000];

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    pre = suf = 0;
    cur = arr[suf];
}

void solve() {
    while (1) {
        if (suf == N)
            break;
        if (cur == M) {
            // cout << pre << " " << suf << " " << cur << "\n";
            cnt++;
            suf++;
            cur += arr[suf];
        } else if (cur < M) {
            suf++;
            cur += arr[suf];
        } else {
            cur -= arr[pre];
            pre++;
        }
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}