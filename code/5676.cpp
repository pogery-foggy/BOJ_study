#include <iostream>
#define MAX_N 100000
using namespace std;

int K, N, tree[MAX_N * 4], arr_index[MAX_N + 1], answer;

int init_tree(int s, int e, int node) {
    if (s == e) {
        int user_in;
        cin >> user_in;
        if (user_in < 0)
            tree[node] = -1;
        else if (user_in > 0)
            tree[node] = 1;
        else
            tree[node] = 0;

        arr_index[s] = node;
        return tree[node];
    }
    int mid = (s + e) >> 1;
    return tree[node] = init_tree(s, mid, node << 1) * init_tree(mid + 1, e, node << 1 | 1);
}

void update(int idx, int dx) {
    int fnd = arr_index[idx];
    if (dx < 0)
        tree[fnd] = -1;
    else if (dx > 0)
        tree[fnd] = 1;
    else
        tree[fnd] = 0;
    fnd >>= 1;
    while (fnd > 0) {
        tree[fnd] = tree[fnd << 1] * tree[fnd << 1 | 1];
        fnd >>= 1;
    }
}

void init() {
    // cin >> N >> K;
    init_tree(0, N - 1, 1);
}

int mult(int s, int e, int l, int r, int node) {
    if (e < l || s > r)
        return 1;
    if (l <= s && e <= r)
        return tree[node];
    int mid = (s + e) >> 1;
    return mult(s, mid, l, r, node << 1) * mult(mid + 1, e, l, r, node << 1 | 1);
}

void solve() {
    for (int i = 0; i < K; i++) {
        char mode;
        cin >> mode;
        if (mode == 'C') {
            int index, dx;
            cin >> index >> dx;
            update(index - 1, dx);
        } else {
            int left, right;
            cin >> left >> right;
            answer = mult(0, N - 1, left - 1, right - 1, 1);
            if (answer < 0)
                cout << '-';
            else if (answer > 0)
                cout << '+';
            else
                cout << 0;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while (cin >> N >> K) {
        init();
        solve();
        cout << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}