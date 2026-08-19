#include <iostream>
#define MAX_N 1000000

typedef long long ll;
using namespace std;

int N, M, K, query, mode, arr_index[MAX_N + 1];
ll tree[4 * MAX_N], arr[MAX_N];

ll init_tree(int s, int e, int node) {
    if (s == e) {
        arr_index[s + 1] = node;
        return tree[node] = arr[s];
    }
    int mid = (s + e) >> 1;
    return tree[node] = init_tree(s, mid, node << 1) + init_tree(mid + 1, e, node << 1 | 1);
}

void update(int idx, long long change) {
    int fnd = arr_index[idx];
    tree[fnd] = change;
    fnd /= 2;
    while (fnd > 0) {
        tree[fnd] = tree[fnd << 1] + tree[fnd << 1 | 1];
        fnd /= 2;
    }
}

ll sum(int s, int e, int l, int r, int node) {
    if (l > e || r < s) {
        return 0;
    }
    if (l <= s && e <= r) {
        return tree[node];
    }
    int mid = (s + e) / 2;
    return sum(s, mid, l, r, node * 2) + sum(mid + 1, e, l, r, node * 2 + 1);
}

void init() {
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    init_tree(0, N - 1, 1);
}

void solve() {
    query = M + K;
    for (int i = 0; i < query; i++) {
        cin >> mode;
        if (mode == 1) { // change
            int idx;
            ll diff;
            cin >> idx >> diff;
            update(idx, diff);
        } else if (mode == 2) { // sum
            int le, ri;
            cin >> le >> ri;
            cout << sum(0, N - 1, le - 1, ri - 1, 1) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
}