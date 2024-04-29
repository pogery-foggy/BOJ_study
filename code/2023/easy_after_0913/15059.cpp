#include <iostream>

using namespace std;
int a, b, c, x, y, z, atotal, xtotal, answer;

void init() {
    cin >> a >> b >> c;
    cin >> x >> y >> z;
}

void solve() {
    if (a < x)
        answer += x - a;
    if (b < y)
        answer += y - b;
    if (c < z)
        answer += z - c;
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}