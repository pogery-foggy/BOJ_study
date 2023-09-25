#include <iostream>

using namespace std;
int x, y;
void init() { cin >> x >> y; }

void solve() {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cout << "*";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}