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
    // cout << x1 << " " << x2 << " " << y1 << " " << y2<<"x\n";
    if (x1 * y2 - x2 * y1 < 0)
        return -1;
    else if (x1 * y2 - x2 * y1 == 0)
        return 0;
    else
        return 1;
}

void solve() {
    int L1a2 = ccw(a1, b1, a2);
    int L1b2 = ccw(a1, b1, b2);
    int L2a1 = ccw(a2, b2, a1);
    int L2b1 = ccw(a2, b2, b1);
    // cout << L1a2 << " " << L1b2 << " " << L2a1 << " " << L2b1<<"L\n";
    // cout << cond1 << " " << cond2 << "\n";
    int cond1 = L1a2 * L1b2;
    int cond2 = L2a1 * L2b1;
    if (cond1 == 0 && cond2 == 0) {
        if (max(a1.x, b1.x) < min(a2.x, b2.x) || max(a2.x, b2.x) < min(a1.x, b1.x) || max(a1.y, b1.y) < min(a2.y, b2.y) || max(a2.y, b2.y) < min(a1.y, b1.y))
            cout << 0;
        else
            cout << 1;
    } else if (cond1 <= 0 && cond2 <= 0)
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