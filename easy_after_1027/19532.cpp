#include <iostream>

using namespace std;
int a, b, c, d, e, f;
void init() { cin >> a >> b >> c >> d >> e >> f; }

void solve() {
    for (int i = -999; i <= 999; i++) {
        for (int j = -999; j <= 999; j++) {
            if (i * a + j * b == c && i * d + j * e == f) {
                cout << i << " " << j;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}