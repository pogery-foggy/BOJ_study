#include <iostream>
#define MAX_N 1000000

using namespace std;

long long tree[MAX_N * 4], lazy_tree[MAX_N * 4];
int N, M, K, mode, from, to;

long long init_tree(int s, int e, int node) {
    if (s == e) {
        cin >> tree[node];
        return tree[node];
    }
    int mid = (s + e) / 2;
    return tree[node] = init_tree(s, mid, node << 1) + init_tree(mid + 1, e, node << 1 | 1);
}

void init() {
    cin >> N >> M >> K;
    init_tree(0, N - 1, 1);
}
void lazy(int s, int e, int node) {
    if (lazy_tree[node]) {
        tree[node] += (e - s + 1) * lazy_tree[node];
        if (s != e) {
            lazy_tree[node << 1] += lazy_tree[node];
            lazy_tree[node << 1 | 1] += lazy_tree[node];
        }
        lazy_tree[node] = 0;
    }
}

void update(int s, int e, int l, int r, int node, long long dx) {
    lazy(s, e, node);
    if (s > r || e < l)
        return;
    if (l <= s && e <= r) {
        tree[node] += (e - s + 1) * dx;
        if (s != e) {
            lazy_tree[node << 1] = lazy_tree[node << 1] + dx;
            lazy_tree[node << 1 | 1] = lazy_tree[node << 1 | 1] + dx;
        }
        return;
    }
    int mid = (s + e) >> 1;
    update(s, mid, l, r, node << 1, dx);
    update(mid + 1, e, l, r, node << 1 | 1, dx);
    tree[node] = tree[node << 1] + tree[node << 1 | 1];
}

long long sum(int s, int e, int l, int r, int node) {
    lazy(s, e, node);
    if (s > r || e < l)
        return 0;
    if (l <= s && e <= r)
        return tree[node];
    int mid = (s + e) >> 1;
    return sum(s, mid, l, r, node << 1) + sum(mid + 1, e, l, r, node << 1 | 1);
}

void solve() {
    for (int i = 0; i < M + K; i++) {
        cin >> mode >> from >> to;
        if (mode == 1) {
            long long dx;
            cin >> dx;
            update(0, N - 1, from - 1, to - 1, 1, dx);
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