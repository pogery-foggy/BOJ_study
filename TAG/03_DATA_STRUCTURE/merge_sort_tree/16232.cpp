#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define MAX_N 200001
typedef long long ll;
using namespace std;

const ll INF = 400000000000000000LL;

int N;
ll a[MAX_N], b[MAX_N], k[MAX_N];
vector<pair<ll, ll>> tree[MAX_N * 4];

vector<pair<ll, ll>> merge_tree(const vector<pair<ll, ll>> &l, const vector<pair<ll, ll>> &r) {
    if (l.empty())
        return r;
    if (r.empty())
        return l;

    int i = 0, j = 0;
    vector<pair<ll, ll>> ret;
    ret.reserve(l.size() + r.size());
    ret.push_back({-INF, l[0].second + r[0].second});

    // 왼쪽 중심으로 융합
    while (true) {
        ll nxt = INF;
        if (i + 1 < l.size())
            nxt = min(nxt, l[i + 1].first);
        if (j + 1 < r.size()) // x + l[i].second](a) = r[j+1].first(y)니까 
            nxt = min(nxt, r[j + 1].first - l[i].second);
        if (nxt == INF)
            break;

        if (i + 1 < l.size() && l[i + 1].first == nxt)
            i++;
        // 넘치면 건너뛰기
        while (j + 1 < r.size() && nxt + l[i].second >= r[j + 1].first)
            j++;

        ll nd = l[i].second + r[j].second;
        // 중복 계산x
        if (ret.back().second != nd) 
            ret.push_back({nxt, nd});
    }
    return ret;
}

void init_tree(int s, int e, int node) {
    if (s == e) { // {구간시작, 값} 미만대신 -INF<=,k<=;
        tree[node].push_back({-INF, a[s]});
        if (a[s] != b[s])
            tree[node].push_back({k[s], b[s]});
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    tree[node] = merge_tree(tree[node << 1], tree[node << 1 | 1]);
}

ll apply(int node, ll x) {
    auto &cur = tree[node];
    int idx = upper_bound(cur.begin(), cur.end(), make_pair(x, INF)) - cur.begin() - 1;
    return x + cur[idx].second;
}

ll query(int s, int e, int l, int r, ll x, int node) {
    if(e < l || r < s) 
        return x;
    if (l <= s && e <= r) // 구간 중 하나 적용
        return apply(node, x);

    int mid = (s + e) >> 1;
    x = query(s, mid, l, r, x, node << 1);
    x = query(mid + 1, e, l, r, x, node << 1 | 1);
    return x;
}

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a[i] >> b[i] >> k[i];
    }
    init_tree(0, N - 1, 1);
}

void solve() {
    for (int i = 0; i < N; i++) {
        ll answer = 0;
        if (i > 0)
            answer = query(0, N - 1, 0, i - 1, answer, 1);
        if (i < N - 1)
            answer = query(0, N - 1, i + 1, N - 1, answer, 1);
        cout << answer << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}