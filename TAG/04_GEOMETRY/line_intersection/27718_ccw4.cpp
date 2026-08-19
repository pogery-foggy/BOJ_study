#include <algorithm>
#include <iostream>
#include <map>
#include <set>

using namespace std;

typedef long long ll;

struct point {
    ll x, y;
};

int n;
point s1[2000], s2[2000];

void init() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s1[i].x >> s1[i].y >> s2[i].x >> s2[i].y;
    }
}

ll ccw(point a, point b, point c) {
    ll x1 = b.x - a.x;
    ll y1 = b.y - a.y;
    ll x2 = c.x - a.x;
    ll y2 = c.y - a.y;

    if (x1 * y2 - x2 * y1 < 0)
        return -1;
    else if (x1 * y2 - x2 * y1 == 0)
        return 0;
    else
        return 1;
}

int intersection(point p1, point p2, point p3, point p4) {
    int l1_p3 = (int)ccw(p1, p2, p3);
    int l1_p4 = (int)ccw(p1, p2, p4);
    int l2_p1 = (int)ccw(p3, p4, p1);
    int l2_p2 = (int)ccw(p3, p4, p2);

    ll cond1 = 1LL * l1_p3 * l1_p4;
    ll cond2 = 1LL * l2_p1 * l2_p2;

    if (l1_p3 == 0 && l1_p4 == 0 && l2_p1 == 0 && l2_p2 == 0) {
        if (max(p1.x, p2.x) < min(p3.x, p4.x) || max(p3.x, p4.x) < min(p1.x, p2.x) || max(p1.y, p2.y) < min(p3.y, p4.y) || max(p3.y, p4.y) < min(p1.y, p2.y))
            return 0;
        return 2;
    }
    if (cond1 <= 0 && cond2 <= 0)
        return 1;
    return 0;
}

bool in_range(ll a, ll b, ll x) {
    if (a > b)
        swap(a, b);
    return a <= x && x <= b;
}

bool on_point(point a, point b, point p) {
    if (ccw(a, b, p) != 0)
        return false;
    return in_range(a.x, b.x, p.x) && in_range(a.y, b.y, p.y);
}

int relation(point p1, point p2, point p3, point p4) {
    if (p1.x != p2.x) {
        ll s = max(min(p1.x, p2.x), min(p3.x, p4.x));
        ll e = min(max(p1.x, p2.x), max(p3.x, p4.x));
        if (s < e)
            return 3;
        if (s == e)
            return 1;
        return 0;
    } else {
        ll s = max(min(p1.y, p2.y), min(p3.y, p4.y));
        ll e = min(max(p1.y, p2.y), max(p3.y, p4.y));
        if (s < e)
            return 3;
        if (s == e)
            return 1;
        return 0;
    }
}

int line(point p1, point p2, point p3, point p4) {
    int type = intersection(p1, p2, p3, p4);

    if (type == 0)
        return 0;

    if (type == 2)
        return relation(p1, p2, p3, p4);

    if (on_point(p1, p2, p3) || on_point(p1, p2, p4) || on_point(p3, p4, p1) || on_point(p3, p4, p2))
        return 1;
    return 2;
}

void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << line(s1[i], s2[i], s1[j], s2[j]);
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}