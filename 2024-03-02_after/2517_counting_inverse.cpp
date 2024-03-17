#include <algorithm>
#include <iostream>
#include <vector>
#define MAX_N 500001
using namespace std;
int N, tree[MAX_N * 4];
int arr[500001];

void init() {
    int idx = 0;
    cin >> N;
    vector<int> fnd_idx;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        fnd_idx.push_back(arr[i]);
    }
    sort(fnd_idx.begin(), fnd_idx.end());
    for (int i = 0; i < N; i++)
        arr[i] = lower_bound(fnd_idx.begin(), fnd_idx.end(), arr[i]) - fnd_idx.begin();
}

void update(int s, int e, int node, int idx) {
    if (idx < s || e < idx)
        return;
    tree[node]++;
    if (s != e) {
        int mid = (s + e) >> 1;
        update(s, mid, node << 1, idx);
        update(mid + 1, e, node << 1 | 1, idx);
    }
}

long long sum(int s, int e, int l, int r, int node) {
    if (r < s || e < l)
        return 0;
    if (l <= s && e <= r)
        return tree[node];
    int mid = (s + e) >> 1;
    return sum(s, mid, l, r, node << 1) + sum(mid + 1, e, l, r, node << 1 | 1);
}

void solve() {
    long long answer = 0;
    for (int i = 0; i < N; i++) {
        int cur = arr[i];
        update(0, N - 1, 1, cur);
        cout << sum(0, N - 1, cur + 1, N - 1, 1) + 1 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}