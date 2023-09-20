#include <iostream>

using namespace std;

int daily, car, cnt;

void init() { cin >> daily; }

void solve() {
    for (int i = 0; i < 5; i++) {
        cin >> car;
        if (car == daily)
            cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}