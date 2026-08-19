#include <iostream>
#include <string>
#include <stack>
using namespace std;

int arr[100001];
int tree[400001];
int N, M;

int init_tree(int s, int e, int node) {
    if (s == e) {
        tree[node] = arr[s];
        return tree[node];
    }
    int mid = (s + e) >> 1;
    int le = init_tree(s, mid, node << 1);
    int ri = init_tree(mid + 1, e, node << 1 | 1);
    if (le == 0) return tree[node] = ri;
    else if (ri == 0) return tree[node] = le;
    else return tree[node] = min(le,ri);
}

void init() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    init_tree(1, N, 1);
}

int mini(int s, int e, int l, int r, int node) {
    if (l <= s && e <= r) return tree[node];
    else if (e < l || r < s) return 0;
    int mid = (s + e) >> 1;
    int le = mini(s, mid, l, r, node << 1);
    int ri = mini(mid + 1, e, l, r, node << 1 | 1);
    if (le == 0) return ri;
    else if (ri == 0) return le;
    else return min(le, ri);
}

void solve() {
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        cout << mini(1,N,a, b, 1) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    
    return 0;
}