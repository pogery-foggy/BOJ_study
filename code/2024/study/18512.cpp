#include <iostream>

using namespace std;
int x, y, p1, p2;
void init() { cin >> p1 >> p2 >> x >> y; }

void solve() {
    while (x != y) {
        if (x > y) {
            y += p2;
        } else {
            x += p1;
        }
        if (x > 100000 || y > 100000) {
            cout << -1;
            return;
        }
    }
    cout << x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}