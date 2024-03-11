#include <iostream>
#include <vector>
#define MAX_N 100001
using namespace std;
typedef pair<long long, long long> pll;
// {홀수, 짝수}
pll tree[MAX_N * 4];
pll arr[MAX_N];
int N, M, arr_index[MAX_N];

pll init_tree(int s, int e, int node) {
    if (s == e) {
        arr_index[s + 1] = node;
        return tree[node] = arr[s];
    }
    int mid = (s + e) >> 1;
    pll l = init_tree(s, mid, node << 1);
    pll r = init_tree(mid + 1, e, node << 1 | 1);
    return tree[node] = {l.first + r.first, l.second + r.second};
}

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        if (!(a % 2))
            arr[i] = {0, 1};
        else
            arr[i] = {1, 0};
    }
    init_tree(0, N - 1, 1);
    cin >> M;
}

void update(pll x, int idx) {
    int fnd = idx;
    tree[fnd] = x;
    fnd /= 2;
    while (fnd > 0) {
        tree[fnd] = {tree[fnd << 1].first + tree[fnd << 1 | 1].first, tree[fnd << 1].second + tree[fnd << 1 | 1].second};
        fnd /= 2;
    }
}

pll sum(int s, int e, int l, int r, int node) {
    if (r < s || e < l)
        return {0, 0};
    if (l <= s && e <= r)
        return tree[node];

    int mid = (s + e) >> 1;
    pll le = sum(s, mid, l, r, node << 1);
    pll ri = sum(mid + 1, e, l, r, node << 1 | 1);
    return {le.first + ri.first, le.second + ri.second};
}

void solve() {
    for (int i = 0; i < M; i++) {
        int query;
        cin >> query;
        switch (query) {
        case 1:
            int x, idx;
            cin >> idx >> x;
            pll cng = x % 2 ? make_pair(1, 0) : make_pair(0, 1);
            update(cng, arr_index[idx]);
            break;
        case 2:
            int l, r;
            cin >> l >> r;
            pll answer = sum(0, N - 1, l - 1, r - 1, 1);
            cout << answer.second << "\n";
            break;
        case 3:
            int l, r;
            cin >> l >> r;
            pll answer = sum(0, N - 1, l - 1, r - 1, 1);
            cout << answer.first << "\n";
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