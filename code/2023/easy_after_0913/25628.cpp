#include <iostream>

using namespace std;
int a, b;

void init() { cin >> a >> b; }

void solve() { cout << min(a / 2, b); }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}