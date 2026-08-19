#include <algorithm>
#include <iostream>
#include <vector>
#define MAX_N 3001
using namespace std;

struct Point {
    int x;
    int y;
};

struct Line {
    Point s;
    Point e;
};

vector<Line> lines;
int N;
int p[MAX_N], total_group;
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        p[i] = -1;
    }
    total_group = N;
    lines.resize(N);
    for (auto &a : lines) {
        cin >> a.s.x >> a.s.y >> a.e.x >> a.e.y;
    }
}

int find_p(int x) {
    if (p[x] < 0)
        return x;
    return p[x] = find_p(p[x]);
}

void union_p(int a, int b) {
    a = find_p(a);
    b = find_p(b);
    if (a == b)
        return;
    if (p[a] > p[b])
        swap(a, b);
    total_group--;
    p[a] += p[b];
    p[b] = a;
}

long long ccw(Point a, Point b, Point c) {
    long long x1 = b.x - a.x;
    long long y1 = b.y - a.y;
    long long x2 = c.x - a.x;
    long long y2 = c.y - a.y;
    if (x1 * y2 - x2 * y1 < 0)
        return -1;
    else if (x1 * y2 - x2 * y1 == 0)
        return 0;
    else
        return 1;
}

bool is_matching(Line l1, Line l2) {
    Point a1 = l1.s;
    Point b1 = l1.e;
    Point a2 = l2.s;
    Point b2 = l2.e;

    int L1a2 = ccw(a1, b1, a2);
    int L1b2 = ccw(a1, b1, b2);
    int L2a1 = ccw(a2, b2, a1);
    int L2b1 = ccw(a2, b2, b1);
    int cond1 = L1a2 * L1b2;
    int cond2 = L2a1 * L2b1;
    if (cond1 == 0 && cond2 == 0) {
        if (max(a1.x, b1.x) < min(a2.x, b2.x) || max(a2.x, b2.x) < min(a1.x, b1.x) || max(a1.y, b1.y) < min(a2.y, b2.y) || max(a2.y, b2.y) < min(a1.y, b1.y))
            return false;
        else
            return true;
    } else if (cond1 <= 0 && cond2 <= 0)
        return true;
    else
        return false;
}

void solve() {
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (!is_matching(lines[i], lines[j]))
                continue;
            int a = find_p(i + 1);
            int b = find_p(j + 1);
            if (a == b)
                continue;
            union_p(a, b);
        }
    }
    int maxi = 0;
    for (int i = 1; i <= N; i++) {
        maxi = max(maxi, -1 * p[i]);
    }
    cout << total_group << "\n" << maxi;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}