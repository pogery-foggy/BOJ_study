#include <algorithm>
#include <iostream>
#define MAX_N 200001
#define INF -21000000
using namespace std;

struct Node {
    int lmx, rmx, mx, sum, ls, rs;
    Node(int x = 0) : lmx(1), rmx(1), mx(1), sum(1), ls(x), rs(x) {}
    Node(int lmx, int rmx, int mx, int sum, int ls, int rs) : lmx(lmx), rmx(rmx), mx(mx), sum(sum), ls(ls), rs(rs) {}
    Node operator+(const Node &t) const {
        Node temp;
        if (rs ^ t.ls && sum == mx)
            temp.lmx = max(sum + t.lmx, lmx);
        else
            temp.lmx = lmx;

        if (rs ^ t.ls && t.sum == t.mx)
            temp.rmx = max(t.sum + rmx, t.rmx);
        else
            temp.rmx = t.rmx;

        if (rs ^ t.ls)
            temp.mx = max({mx, t.mx, rmx + t.lmx});
        else
            temp.mx = max(mx, t.mx);
        temp.sum = sum + t.sum;

        temp.ls = ls;
        temp.rs = t.rs;
        return temp;
    }
};

Node tree[MAX_N * 4];
int N, M, Q, arr[MAX_N], arr_index[MAX_N];

Node init_tree(int s = 0, int e = N - 1, int node = 1) {
    if (s == e) {
        arr_index[s + 1] = node;
        return tree[node] = Node(arr[s]);
    }
    int mid = (s + e) >> 1;
    return tree[node] = init_tree(s, mid, node << 1) + init_tree(mid + 1, e, node << 1 | 1);
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
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        arr[i] = 0;
    }
    init_tree(0, N - 1, 1);
}

void solve() {
    for (int i = 0; i < Q; i++) {
        int idx;
        cin >> idx;
        arr[idx - 1] ^= 1;
        update(idx, arr[idx - 1]);
        cout << tree[1].mx << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}