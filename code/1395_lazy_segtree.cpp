#include <iostream>
#define MAX_N 100000

using namespace std;

int tree[MAX_N * 4], lazy_tree[MAX_N * 4];
int N, M, mode, from, to;
void init() { cin >> N >> M; }
void lazy(int s, int e, int node) {
    if (lazy_tree[node]) {
        tree[node] = (e - s + 1) - tree[node];
        if (s != e) {
            lazy_tree[node << 1] = !lazy_tree[node << 1];
            lazy_tree[node << 1 | 1] = !lazy_tree[node << 1 | 1];
        }
        lazy_tree[node] = 0;
    }
}

void update(int s, int e, int l, int r, int node) {
    lazy(s, e, node);
    if (s > r || e < l)
        return;
    if (l <= s && e <= r) {
        tree[node] = (e - s + 1) - tree[node];
        if (s != e) {
            lazy_tree[node << 1] = !lazy_tree[node << 1];
            lazy_tree[node << 1 | 1] = !lazy_tree[node << 1 | 1];
        }
        return;
    }
    int mid = (s + e) >> 1;
    update(s, mid, l, r, node << 1);
    update(mid + 1, e, l, r, node << 1 | 1);
    tree[node] = tree[node << 1] + tree[node << 1 | 1];
}

int sum(int s, int e, int l, int r, int node) {
    lazy(s, e, node);
    if (s > r || e < l)
        return 0;
    if (l <= s && e <= r)
        return tree[node];
    int mid = (s + e) >> 1;
    return sum(s, mid, l, r, node << 1) + sum(mid + 1, e, l, r, node << 1 | 1);
}

void solve() {
    for (int i = 0; i < M; i++) {
        cin >> mode >> from >> to;
        if (!mode) {
            update(0, N - 1, from - 1, to - 1, 1);
        } else {
            cout << sum(0, N - 1, from - 1, to - 1, 1) << "\n";
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    solve();
    return 0;
}