#include <algorithm>
#include <iostream>
#include <vector>
#define MAX_N 50001
#define INF 2147000000
using namespace std;
typedef pair<int, int> pii;

pii tree[MAX_N * 4], arr[MAX_N];
int N, Q, arr_index[MAX_N + 1];

pii init_tree(int s, int e, int node) {
    if (s == e) {
        arr_index[s] = node;
        return tree[node] = arr[s];
    }
    int mid = (s + e) >> 1;
    pii l = init_tree(s, mid, node << 1);
    pii r = init_tree(mid + 1, e, node << 1 | 1);
    return tree[node] = pair{max(l.first, r.first), min(l.second, r.second)};
}

void init() {
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        arr[i] = {a, a};
    }
    init_tree(0, N - 1, 1);
}

pii sum(int s, int e, int l, int r, int node) {
    if (r < s || e < l)
        return pair{0, INF};
    if (l <= s && e <= r)
        return tree[node];
    int mid = (s + e) >> 1;
    pii le = sum(s, mid, l, r, node << 1);
    pii ri = sum(mid + 1, e, l, r, node << 1 | 1);

    return pair{max(le.first, ri.first), min(le.second, ri.second)};
}

void solve() {
    for (int i = 0; i < Q; i++) {
        int r, l;
        cin >> l >> r;
        pii answer = sum(0, N - 1, l - 1, r - 1, 1);
        cout << answer.first - answer.second << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}