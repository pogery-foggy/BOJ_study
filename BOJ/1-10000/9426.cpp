#include <iostream>
#define MAX_T 65536
#define MAX_N 250001
using namespace std;

int tree[MAX_T * 4];
int arr_index[MAX_T], arr[MAX_N];
long long N, K, answer;

void init_tree(int s, int e, int node) {
    if (s == e) {
        arr_index[s] = node;
        return;
    }
    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    return;
}

void init() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    init_tree(0, MAX_T - 1, 1);
}

int fnd(int s, int e, int node, int rank) {
    if (s == e)
        return s;
    int mid = (s + e) >> 1;
    if (tree[node << 1] >= rank)
        return fnd(s, mid, node << 1, rank);
    else
        return fnd(mid + 1, e, node << 1 | 1, rank - tree[node << 1]);
}

void update(int idx, int num) {
    int node = arr_index[idx];
    while (node > 0) {
        tree[node] += num;
        node >>= 1;
    }
}

void solve() {
    for (int i = 0; i < K; i++) {
        update(arr[i], 1);
    }
    int mid_rank = (K + 1) / 2;
    answer += fnd(0, MAX_T - 1, 1, mid_rank);
    for (int i = K; i < N; i++) {
        update(arr[i - K], -1);
        update(arr[i], 1);
        answer += fnd(0, MAX_T - 1, 1, mid_rank);
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