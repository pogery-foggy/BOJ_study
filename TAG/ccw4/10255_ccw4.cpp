#include <algorithm>
#include <iostream>
#include <map>
#include <set>

using namespace std;
typedef long long ll;
struct point {
    ll x, y;
};
point a1, b1; // 사각형
point a2, b2; // 선
ll minx, miny, maxx, maxy;
void init() {
    cin >> minx >> miny >> maxx >> maxy;
    cin >> a2.x >> a2.y >> b2.x >> b2.y;
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

bool kiss(point a, point b, point c, point d) {
    if (a.x == b.x) { // 수직
        ll s = max(min(a.y, b.y), min(c.y, d.y));
        ll e = min(max(a.y, b.y), max(c.y, d.y));
        return s < e;
    } else { // 수평
        ll s = max(min(a.x, b.x), min(c.x, d.x));
        ll e = min(max(a.x, b.x), max(c.x, d.x));
        return s < e;
    }
}

bool is_vertex(point p) {
    if ((p.x == minx || p.x == maxx) && (p.y == miny || p.y == maxy))
        return true;
    return false;
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

int solve() {
    point v[4] = {{minx, miny}, {maxx, miny}, {maxx, maxy}, {minx, maxy}};

    int cnt = 0;
    map<pair<ll, ll>, int> hit;

    for (int i = 0; i < 4; i++) {
        a1 = v[i];
        b1 = v[(i + 1) % 4];

        int type = intersection(a1, b1, a2, b2);
        if (type == 0)
            continue;

        if (type == 2) {
            if (a1.x == b1.x) { // 수직 변
                ll s = max(min(a1.y, b1.y), min(a2.y, b2.y));
                ll e = min(max(a1.y, b1.y), max(a2.y, b2.y));
                if (s < e)
                    return 4;
                // s==e: 한 점
                cnt += 1;
                point p = {a1.x, s};
                if (is_vertex(p))
                    hit[{p.x, p.y}]++;
            } else { // 수평 변
                ll s = max(min(a1.x, b1.x), min(a2.x, b2.x));
                ll e = min(max(a1.x, b1.x), max(a2.x, b2.x));
                if (s < e)
                    return 4;
                cnt += 1;
                point p = {s, a1.y};
                if (is_vertex(p))
                    hit[{p.x, p.y}]++;
            }
        } else { // 꼭지점이 선분을 지나는지
            cnt += 1;
            for (int k = 0; k < 4; k++) {
                if (!is_vertex(v[k]))
                    continue;
                if (on_point(a1, b1, v[k]) && on_point(a2, b2, v[k]))
                    hit[{v[k].x, v[k].y}]++;
            }
        }
    }

    cnt -= (int)hit.size();

    if (cnt < 0)
        cnt = 0;
    if (cnt > 2)
        cnt = 2;
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        cout << solve() << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}