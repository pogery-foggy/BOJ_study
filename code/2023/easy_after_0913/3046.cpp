#include <iostream>

using namespace std;

int r1,r2,s;
void init() {
    cin >> r1 >> s;
}

void solve() {
    r2 = 2*s - r1;
    cout << r2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}