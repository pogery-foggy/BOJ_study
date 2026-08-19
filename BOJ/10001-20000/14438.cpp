#include <iostream>
#define MAX_N 100000
using namespace std;

int tree[4 * MAX_N], N, M, arr[MAX_N], arr_index[MAX_N], answer;

int init_tree(int s, int e, int node) {
    if (s == e) {
        tree[node] = arr[s];
        arr_index[s] = node;
        return tree[node];
    }

    int mid = (s + e) >> 1;

    return tree[node] = min(init_tree(s, mid, node << 1), init_tree(mid + 1, e, node << 1 | 1));
}

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    init_tree(0, N - 1, 1);
    cin >> M;
}

void update(int idx, int change) {
    int node = arr_index[idx];
    tree[node] = change;
    node >>= 1;

    while (node > 0) {
        tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
        node >>= 1;
    }
}

int fnd(int s, int e, int l, int r, int node) {
    if (r < s || e < l)
        return 1000000001;
    if (l <= s && e <= r)
        return tree[node];

    int mid = (s + e) >> 1;
    int le = fnd(s, mid, l, r, node << 1);
    int ri = fnd(mid + 1, e, l, r, node << 1 | 1);

    return min(le, ri);
}

void solve() {
    int mode;

    for (int i = 0; i < M; i++) {
        cin >> mode;
        if (mode == 1) {
            int index, change;
            cin >> index >> change;
            update(index - 1, change);
        } else {
            int l, r;
            cin >> l >> r;
            answer = fnd(0, N - 1, l - 1, r - 1, 1);
            cout << answer << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    solve();
}