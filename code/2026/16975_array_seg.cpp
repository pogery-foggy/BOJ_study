#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#define MAX_N 100000
typedef long long ll;
using namespace std;

ll tree[MAX_N * 4];
ll arr[MAX_N * 4];
int N;
// 차분 배열 트릭

int init_tree(int s, int e, int node) { // 만들필요는 없지만 세그 재활을 위해
    if (s == e)
        return tree[node] = 0;
    int mid = (s + e) >> 1;
    return tree[node] = init_tree(s, mid, node << 1) + init_tree(mid + 1, e, node << 1 | 1);
}

void init() {
    cin >> N;
    init_tree(0, N - 1, 1);
    for (int i = 0; i < N; i++)
        cin >> arr[i];
}

void update(int s, int e, int node, int l, int r, int dx) {
    if (r < s || e < l)
        return;
    if (l <= s && e <= r) {
        tree[node] += (e - s + 1) * dx;
        return;
    }
    int mid = (s + e) >> 1;
    update(s, mid, node << 1, l, r, dx);
    update(mid + 1, e, node << 1 | 1, l, r, dx);
    tree[node] = tree[node << 1] + tree[node << 1 | 1];
}

ll sum(int s, int e, int node, int l, int r) {
    if (r < s || e < l)
        return 0;
    if (l <= s && e <= r) {
        return tree[node];
    }
    int mid = (s + e) >> 1;
    return sum(s, mid, node << 1, l, r) + sum(mid + 1, e, node << 1 | 1, l, r);
}

void solve() {
    int M;
    cin >> M;
    while (M--) {
        int type;
        cin >> type;
        if (type == 1) {
            ll l, r, dx;
            cin >> l >> r >> dx;
            update(0, N - 1, 1, l - 1, l - 1, dx);
            if (r < N)
                update(0, N - 1, 1, r, r, -dx);
        } else {
            ll x;
            cin >> x;
            cout << arr[x - 1] + sum(0, N - 1, 1, 0, x - 1) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}