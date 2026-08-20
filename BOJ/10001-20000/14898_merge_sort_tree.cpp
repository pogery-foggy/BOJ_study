#include <algorithm>
#include <iostream>
#include <vector>
#define MAX_N 1000001
using namespace std;
int N, Q;
int arr[MAX_N];  
int prv[MAX_N];   
vector<int> tree[MAX_N * 4]; 

void init_tree(int s, int e, int node) {
    if (s == e) {
        tree[node].push_back(prv[s]);
        return;
    }
    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);

    auto &L = tree[node << 1];
    auto &R = tree[node << 1 | 1];
    tree[node].resize(int(L.size() + R.size()));
    merge(L.begin(), L.end(), R.begin(), R.end(), tree[node].begin());
}

// prv가 결국 last의 위치를 담고 있으므로 
// 구간내에서 prv[i]를 찾았을때 현재 구간안에 없으면 걔는 해당하는거
// 지금 정렬이 되어있으니까 현재구간(L)보다 커지는 애 기준 - 시작점 빼면 개수
int query(int s, int e, int l, int r, int node, int x) {
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) {
        auto &cur = tree[node];
        return lower_bound(cur.begin(), cur.end(), x) - cur.begin();
    }
    int mid = (s + e) >> 1;
    return query(s, mid, l, r, node << 1, x) + query(mid + 1, e, l, r, node << 1 | 1, x);
}

void init() {
    cin >> N;

    vector<int> comp;
    comp.reserve(N);

    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        comp.push_back(arr[i]);
    }

    // 좌표압축
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for (int i = 1; i <= N; i++) {
        arr[i] = lower_bound(comp.begin(), comp.end(), arr[i]) - comp.begin();
    }

    // 이전에 있던 값이라면 last가 갱신됨
    vector<int> last(comp.size(), 0);
    for (int i = 1; i <= N; i++) {
        int v = arr[i];
        prv[i] = last[v];
        last[v] = i;
    }
    init_tree(1, N, 1);
}

void solve() {
    int ans = 0;
    cin >> Q;
    while (Q--) {
        int x, r;
        cin >> x >> r;
        // 여기서 0-based로 하면 깨지는 듯? 나중에 다시 풀어볼까
        int l = x + ans;
        ans = query(1, N, l, r, 1, l);
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    solve();
    return 0;
}