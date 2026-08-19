#include <iostream>

using namespace std;

long long N, D, cnt, V, F, C;
void init() {
    cin >> N >> D;
    cnt = 0;
}

void solve() {
    for (int i = 0; i < N; i++) {
        cin >> V >> F >> C;
        if ((D * C) <= F * V)
            cnt++;
    }
    cout << cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}