#include <algorithm>
#include <iostream>
#define MAX_N 100001
#define INF -21000000
using namespace std;

struct Node {
    int lmx, rmx, mx, sum;
    Node(int x = 0) : lmx(x), rmx(x), mx(x), sum(x) {}
    Node(int lmx, int rmx, int mx, int sum) : lmx(lmx), rmx(rmx), mx(mx), sum(sum) {}
    Node operator+(const Node &t) const { return Node(max(sum + t.lmx, lmx), max(t.sum + rmx, t.rmx), max({mx, t.mx, rmx + t.lmx}), sum + t.sum); }
};

Node tree[MAX_N * 4];
int N, M, Q, U, V, arr[MAX_N], arr_index[MAX_N];

Node init_tree(int s = 0, int e = N - 1, int node = 1) {
    if (s == e) {
        arr_index[s + 1] = node;
        return tree[node] = Node(U * arr[s] + V);
    }
    int mid = (s + e) >> 1;
    return tree[node] = init_tree(s, mid, node << 1) + init_tree(mid + 1, e, node << 1 | 1);
}

Node query(int s, int e, int l, int r, int node = 1) {
    if (l > e || r < s)
        return Node(INF);
    if (l <= s && e <= r)
        return tree[node];
    int mid = (s + e) >> 1;
    return query(s, mid, l, r, node << 1) + query(mid + 1, e, l, r, node << 1 | 1);
}

void update(int idx, int change) {
    int fnd = arr_index[idx];
    tree[fnd] = Node(change);
    fnd /= 2;
    while (fnd > 0) {
        tree[fnd] = tree[fnd << 1] + tree[fnd << 1 | 1];
        fnd /= 2;
    }
}

void init() {
    cin >> N >> Q >> U >> V;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    init_tree(0, N - 1, 1);
}

void solve() {
    for (int i = 0; i < Q; i++) {
        int mode;
        cin >> mode;
        if (!mode) {
            int t1, t2;
            cin >> t1 >> t2;
            Node answer = query(1, N, t1, t2, 1);
            cout << answer.mx - V << "\n";
        } else {
            int idx, num;
            cin >> idx >> num;
            update(idx, U * num + V);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}