#include <algorithm>
#include <iostream>
#include <vector>
#define MAX_N 2001
using namespace std;

int N, M;
vector<pair<int, int>> arr;
long long tree[4 * MAX_N];
void init() {
    cin >> N >> M;
    arr.resize(M);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        arr[i] = {a, b};
    }
    sort(arr.begin(), arr.end());
}

void update(int s, int e, int node, int idx) {
    if (s > idx || e < idx)
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
    for (int i = 0; i < M; i++) {
        int cur = arr[i].second;
        update(0, N - 1, 1, cur - 1);
        answer += sum(0, N - 1, cur, N - 1, 1);
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