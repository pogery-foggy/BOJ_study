#include <algorithm>
#include <iostream>
#include <vector>
#define MAX_N 500001
using namespace std;
int tree[MAX_N * 4];
int fnd_idx[1000001];
vector<pair<int, int>> arr;
int N;
void init() {
    int idx = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        fnd_idx[a] = idx++;
    }
    for (int j = 0; j < N; j++) {
        int a;
        cin >> a;
        arr.push_back({a, fnd_idx[a]});
    }
    // sort(arr.begin(), arr.end());
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
        int cur = arr[i].second;
        update(0, N - 1, 1, cur);
        answer += sum(0, N - 1, cur + 1, N - 1, 1);
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}