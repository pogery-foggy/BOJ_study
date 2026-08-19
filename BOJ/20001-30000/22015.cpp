#include <iostream>

using namespace std;

int a, b, c, maxi;

void init() { cin >> a >> b >> c; }

void solve() {
    maxi = max(a, b);
    maxi = max(maxi, c);
    cout << (maxi * 3) - a - b - c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}