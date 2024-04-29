#include <iostream>
#include <vector>
#define MAX_N 500000
using namespace std;

int answer, N, M;
long long tree[4 * MAX_N + 1];
int soldier[MAX_N], arr_index[MAX_N];

long long tree_init(int s, int e, int node) {
    if (s == e) {
        arr_index[s] = node;
        return tree[node] = soldier[s];
    }
    int mid = (s + e) / 2;
    return tree[node] = tree_init(s, mid, node << 1) + tree_init(mid + 1, e, node << 1 | 1);
}

void init() {
    answer = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> soldier[i];
    }
    tree_init(0, N - 1, 1);
}

void mode1(int index, int diff) {
    int fnd = arr_index[index - 1];
    while (fnd > 0) {
        tree[fnd] += diff;
        fnd /= 2;
    }
}

int mode2(int s, int e, int node, int sol) {

    if (s == e)
        return s + 1;

    if (tree[node * 2] >= sol) // 등호가 들어가야 하는가?
        return mode2(s, (s + e) / 2, node * 2, sol);
    else {
        return mode2((s + e) / 2 + 1, e, node * 2 + 1, sol - tree[node * 2]);
    }
}

void solve() {
    cin >> M;
    for (int i = 0; i < M; i++) {
        int mode;
        cin >> mode;
        if (mode == 1) {
            int idx, dif;
            cin >> idx >> dif;
            mode1(idx, dif);
        } else {
            int idx;
            cin >> idx;
            cout << mode2(0, N - 1, 1, idx) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    // cout << answer << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}