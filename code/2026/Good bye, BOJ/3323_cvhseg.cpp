#include <algorithm>
#include <iostream>
#include <vector>
#define MAX_N 100001
typedef long long ll;
using namespace std;

struct Point{
    ll x, y;
};

Point zero = {0, 0};
vector<Point> star;
vector<Point> tree[MAX_N * 4];
int N, M;

ll ccw(Point a, Point b, Point c){
    ll x1 = b.x - a.x;
    ll y1 = b.y - a.y;
    ll x2 = c.x - a.x;
    ll y2 = c.y - a.y;
    return x1 * y2 - x2 * y1;
}

ll dist(Point a, Point b){
    ll dx = a.x - b.x;
    ll dy = a.y - b.y;
    return dx * dx + dy * dy;
}

bool comp(Point a, Point b){
    ll d = ccw(zero, a, b);
    if(d > 0)
        return true;
    if(d < 0)
        return false;
    return dist(zero, a) < dist(zero, b);
}

void compress(){
    vector<Point> temp;
    for(auto a : star){
        if(temp.empty() || ccw(zero, temp.back(), a) != 0)
            temp.push_back(a);
    }
    star = temp;
    N = star.size();
}

void push_tree(int s, int e, int node, int idx){
    tree[node].push_back(star[idx]);
    if(s == e)
        return;

    int mid = (s + e) >> 1;
    if(idx <= mid)
        push_tree(s, mid, node << 1, idx);
    else
        push_tree(mid + 1, e, node << 1 | 1, idx);
}

void make_hull(int node){
    vector<Point> convex;
    for(auto p : tree[node]){
        while(convex.size() >= 2){
            Point a = convex[convex.size() - 2];
            Point b = convex[convex.size() - 1];
            if(ccw(a, b, p) < 0)
                break;
            convex.pop_back();
        }
        convex.push_back(p);
    }
    tree[node] = convex;
}

void init_tree(int s, int e, int node){
    make_hull(node);
    if(s == e)
        return;

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
}

bool is_inside(int node, Point a, Point b){
    auto &convex = tree[node];
    int l = 0;
    int r = convex.size() - 1;
    while(l + 3 < r){
        int m1 = (l + l + r) / 3;
        int m2 = (l + r + r) / 3;
        if(ccw(a, b, convex[m1]) < ccw(a, b, convex[m2]))
            l = m1;
        else
            r = m2;
    }

    ll maxi = -4000000000000000000LL;
    for(int i = l; i <= r; i++){
        maxi = max(maxi, ccw(a, b, convex[i]));
    }
    return maxi > 0;
}

bool query(int s, int e, int l, int r, Point a, Point b, int node){
    if(r < s || e < l)
        return false;
    if(l <= s && e <= r)
        return is_inside(node, a, b);

    int mid = (s + e) >> 1;
    if(query(s, mid, l, r, a, b, node << 1))
        return true;
    if(query(mid + 1, e, l, r, a, b, node << 1 | 1))
        return true;
    return false;
}

int get_left(Point a){
    int l = 0;
    int r = N - 1;
    int ret = N;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(ccw(zero, a, star[mid]) > 0){
            ret = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return ret;
}

int get_right(Point b){
    int l = 0;
    int r = N - 1;
    int ret = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(ccw(zero, b, star[mid]) < 0){
            ret = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    return ret;
}

void init(){
    cin >> N >> M;
    star.resize(N);
    for(auto &a : star){
        cin >> a.x >> a.y;
    }

    sort(star.begin(), star.end(), comp);
    compress();
    for(int i = 0; i < N; i++){
        push_tree(0, N - 1, 1, i);
    }
    init_tree(0, N - 1, 1);
}

void solve() {
    while(M--){
        Point a, b;
        cin >> a.x >> a.y >> b.x >> b.y;
        if(ccw(zero, a, b) < 0){
            Point temp = a;
            a = b;
            b = temp;
        }

        int l = get_left(a);
        int r = get_right(b);
        if(l > r){
            cout << "N\n";
            continue;
        }

        if(query(0, N - 1, l, r, a, b, 1))
            cout << "Y\n";
        else
            cout << "N\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}
