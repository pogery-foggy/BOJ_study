#include <iostream>

using namespace std;

int x, cnt;

void init() { cin >> x; }

void solve() {
    for (int i = 0; i < 7; i++) {
        if (x & (1 << i))
            cnt++;
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