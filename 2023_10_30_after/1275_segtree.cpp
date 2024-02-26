#include <iostream>
#define MAX_N 100000
using namespace std;

typedef long long ll;

ll N, Q, arr_index[MAX_N + 1];
ll tree[MAX_N * 4], arr[MAX_N];

ll init_tree(int s, int e, int node) {
    if (s == e) {
        arr_index[s + 1] = node;
        return tree[node] = arr[s];
    }
    int mid = (s + e) >> 1;
    return tree[node] = init_tree(s, mid, node << 1) + init_tree(mid + 1, e, node << 1 | 1);
}

void update(int idx, long long change) {
    ll fnd = arr_index[idx];
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
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    init_tree(0, N - 1, 1);
}

void max_a(int &a, int &b){
    if(a>b){
        int temp = b;
        b = a;
        a = temp;
    }
}

void solve() {
    for (int i = 0; i < Q; i++) {
        int le, ri;
        cin >> le >> ri;
        max_a(le,ri);
        cout << sum(0, N - 1, le - 1, ri - 1, 1) << "\n";
        ll idx, chg;
        cin >> idx >> chg;
        update(idx, chg);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}