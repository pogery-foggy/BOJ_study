#include <iostream>

using namespace std;

int a1, a2, a3, a4, a5, a6;
int s, e, ar1, ar2, ar3, ar4, ar5, ar6;
void init() { cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6; }

void solve() {
    s = (a1 * 3600) + (a2 * 60) + a3;
    e = (a4 * 3600) + (a5 * 60) + a6;
    ar1 = e - s;
    ar2 = ar1 / 3600;
    ar3 = (ar1 % 3600) / 60;
    ar4 = (ar1 % 3600) % 60;

    cout << ar2 << " " << ar3 << " " << ar4 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 3; i++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}