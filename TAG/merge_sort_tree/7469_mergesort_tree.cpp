#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#define MAX_N 100000
typedef long long ll;
using namespace std;

vector<int> tree[MAX_N * 4];
int arr[MAX_N];
int N, Q;
// 머지 소트 트리

void init_tree(int s, int e, int node) {
    if (s == e) {
        tree[node].push_back(arr[s]);
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    auto &l = tree[node << 1];
    auto &r = tree[node << 1 | 1];
    tree[node].resize(int(l.size() + r.size()));
    merge(l.begin(), l.end(), r.begin(), r.end(), tree[node].begin());
}

void init() {
    cin >> N >> Q;
    for (int i = 0; i < N; i++)
        cin >> arr[i];
    init_tree(0, N - 1, 1);
    sort(arr, arr+N);
}

int query(int s, int e, int l, int r, int node,int x) {
    if (r < s || e < l)
        return 0;
    if (l <= s && e <= r) {
        auto &cur = tree[node];
        return upper_bound(cur.begin(), cur.end(), x) - cur.begin();
    }
    int mid = (s + e) >> 1;
    return query(s,mid,l,r,node<<1,x) + query(mid+1,e,l,r,node<<1|1,x);
}

void solve() {
    while (Q--) {
        int l, r, k;
        cin >> l >> r >> k;
        int lo = 0, hi = N-1;
        while(lo < hi){
            int mid = (lo+hi) >> 1;
            int fnd = arr[mid];
            int cnt = query(0, N - 1, l - 1, r - 1, 1, fnd);
            if(cnt >= k) hi = mid;
            else lo = mid+1;
        }
        cout << arr[hi] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}