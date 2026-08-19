#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#define MAX_N 100000
typedef long long ll;
using namespace std;

vector<int> tree[MAX_N * 4];
int arr[MAX_N];
int N;
// 머지 소트 트리

void init_tree(int s, int e, int node) {
    if (s == e) {
        tree[node].push_back(arr[s]);
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    auto &l = tree[node << 1];
    auto &r = tree[node << 1 | 1];
    tree[node].resize(int(l.size() + r.size()));
    merge(l.begin(), l.end(), r.begin(), r.end(), tree[node].begin());
}

void init() {
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i];
    init_tree(0, N - 1, 1);
}

int query(int s, int e, int l, int r, int x, int node) {
    if (r < s || e < l)
        return 0;
    if (l <= s && e <= r) {
        auto &cur = tree[node];
        return cur.end() - upper_bound(cur.begin(), cur.end(), x);
    }
    int mid = (s + e) >> 1;
    return query(s, mid, l, r, x, node << 1) + query(mid + 1, e, l, r, x, node << 1 | 1);
}

void solve() {
    int Q;
    cin >> Q;
    while (Q--) {
        int l, r, x;
        cin >> l >> r >> x;
        cout << query(0, N - 1, l - 1, r - 1, x, 1) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}