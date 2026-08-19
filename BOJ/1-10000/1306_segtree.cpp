#include <algorithm>
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
    return tree[node] = max(init_tree(s, mid, node << 1), init_tree(mid + 1, e, node << 1 | 1));
}

ll sum(int s, int e, int l, int r, int node) {
    if (l > e || r < s) {
        return -1;
    }
    if (l <= s && e <= r) {
        return tree[node];
    }
    int mid = (s + e) / 2;
    return max(sum(s, mid, l, r, node * 2), sum(mid + 1, e, l, r, node * 2 + 1));
}

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    init_tree(0, N - 1, 1);
}

void solve() {
    for (int i = M; i <= N - M + 1; i++) {
        int l = i - M + 1;
        int r = i + M - 1;
        cout << sum(0, N - 1, l - 1, r - 1, 1) << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
}