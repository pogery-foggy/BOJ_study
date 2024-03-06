#include <iostream>
#define MAX_N 200001
using namespace std;

int tree[MAX_N * 4];
int N, M;
int arr[MAX_N], query[100001], posi[100001];

int init_tree(int s, int e, int node) {
    if (s == e) {
        return tree[node] = arr[s];
    }
    int mid = (s + e) >> 1;
    return tree[node] = init_tree(s, mid, node >> 1) + init_tree(mid + 1, e, node >> 1 | 1);
}

void init() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> query[i];
    }
    for (int i = 1; i <= N + M; i++) {
        arr[i] = 0;
    }
    for (int i = 1; i <= N; i++) {
        arr[i] = 1;
        posi[i] = N - i + 1;
    }

    init_tree(1, N + M, 1);
}

void update(int s, int e, int idx, int diff, int node) {
    if (s <= idx && idx <= e) {
        tree[node] += diff;
        if (s != e) {
            int mid = (s + e) >> 1;
            update(s, mid, idx, diff, node >> 1);
            update(mid + 1, e, idx, diff, node >> 1 | 1);
        }
    }
}

int sum(int s, int e, int l, int r, int node) {
    if (r < s || e < l)
        return 0;
    if (l <= s && e <= r)
        return tree[node];

    int mid = (s + e) >> 1;

    return sum(s, mid, l, r, node >> 1) + sum(mid + 1, e, l, r, node >> 1 | 1);
}

void solve() {
    for (int i = 0; i < M; i++) {
        int cur = query[i];
        int cur_position = posi[cur];
        int next_position = N + i + 1;
        update(1, N + M, cur_position, -1, 1);
        update(1, N + M, next_position, 1, 1);
        posi[cur] = next_position;
        cout << sum(1, N + M, cur_position, next_position - 1, 1) << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}