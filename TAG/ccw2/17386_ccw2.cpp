#include <iostream>

using namespace std;

struct Point {
    long long x, y;
};
Point a1, b1, a2, b2;
void init() {
    cin >> a1.x >> a1.y;
    cin >> b1.x >> b1.y;
    cin >> a2.x >> a2.y;
    cin >> b2.x >> b2.y;
}

long long ccw(Point a, Point b, Point c) {
    long long x1 = b.x - a.x;
    long long y1 = b.y - a.y;
    long long x2 = c.x - a.x;
    long long y2 = c.y - a.y;
    if (x1 * y2 - x2 * y1 < 0)
        return -1;
    else
        return 1;
    // return x1 * y2 - x2 * y1;
}

void solve() {
    // cond 1
    bool cond1 = ((ccw(a1, b1, a2) * ccw(a1, b1, b2)) < 0);
    bool cond2 = ((ccw(a2, b2, a1) * ccw(a2, b2, b1)) < 0);
    if (cond1 && cond2)
        cout << 1;
    else
        cout << 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}