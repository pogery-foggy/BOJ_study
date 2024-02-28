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
int N, M, arr[MAX_N];

Node init_tree(int s = 0, int e = N - 1, int node = 1) {
    if (s == e)
        return tree[node] = Node(arr[s]);
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

void init() {
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i];
    init_tree();
    cin >> M;
}

void solve() {
    for (int i = 0; i < M; i++) {
        int t1, t2;
        cin >> t1 >> t2;
        cout << query(1, N, t1, t2).mx << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}