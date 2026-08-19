#include <iostream>
#include <vector>
#define MAX_N 100000
using namespace std;

int N, M, mode, a, v;
pair<int, int> tree[MAX_N * 4];
int arr_index[MAX_N + 1];

pair<int, int> init_tree(int s, int e, int node) {
    if (s == e) {
        cin >> tree[node].first;
        tree[node].second = s + 1;
        arr_index[s + 1] = node;
        return tree[node];
    }
    int mid = (s + e) >> 1;
    pair<int, int> left = init_tree(s, mid, node << 1);
    pair<int, int> right = init_tree(mid + 1, e, node << 1 | 1);
    return tree[node] = {left.first <= right.first ? left : right};
}

void init() {
    cin >> N;
    init_tree(0, N - 1, 1);
}

void update(int idx, int change) {
    int fnd = arr_index[idx];
    tree[fnd].first = change;
    fnd >>= 1;
    while (fnd > 0) {
        tree[fnd] = tree[fnd << 1].first <= tree[fnd << 1 | 1].first ? tree[fnd << 1] : tree[fnd << 1 | 1];
        fnd >>= 1;
    }
}

void solve() {
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> mode;
        if (mode == 1) {
            cin >> a >> v;
            update(a, v);
        } else if (mode == 2) {
            cout << tree[1].second << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}