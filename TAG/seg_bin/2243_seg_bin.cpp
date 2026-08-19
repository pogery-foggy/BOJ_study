#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_N 1000001
using namespace std;

int tree[MAX_N * 4];
int arr_index[MAX_N];
int N, ret;
int init_tree(int s, int e, int node) {
    if (s == e) {
        tree[node] = 0;
        arr_index[s] = node;
        return 0;
    }
    int mid = (s + e) >> 1;
    return tree[node] = init_tree(s, mid, node << 1) + init_tree(mid + 1, e, node << 1 | 1);
}

void init() {
    cin >> N;
    init_tree(0, MAX_N - 1, 1);
}

int fnd(int s, int e, int node, int grade) {
    if (s == e) return s;
    int mid = (s + e) >> 1;
    if (tree[node << 1] >= grade) {
        return fnd(s, mid, node << 1, grade);
    }
    else {
        return fnd(mid + 1, e, node << 1 | 1, grade - tree[node << 1]);
    }
}

void update(int idx, int num) {
    int node = arr_index[idx];
    while (node > 0) {
        tree[node] += num;
        node >>= 1;
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        int query;
        cin >> query;
        if (query == 1) {
            int grade;
            cin >> grade;
            int ans = fnd(0, MAX_N - 1, 1, grade);
            cout << ans << "\n";
            update(ans, -1);
        }
        else if (query == 2) {
            int idx, num;
            cin >> idx >> num;
            update(idx, num);
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