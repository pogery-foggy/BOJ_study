#include <iostream>

using namespace std;

int x, y;
void init() { cin >> x >> y; }

void solve() {

    if (y > x)
        cout << y - x;
    else
        cout << y + x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}