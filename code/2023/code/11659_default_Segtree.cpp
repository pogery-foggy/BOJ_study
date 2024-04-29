#include <iostream>
#define MAX_N 100000
using namespace std;

int tree[4 * MAX_N];
int answer, N, M;

int init_tree(int s, int e, int node) {
    if (s == e) {
        cin >> tree[node];
        return tree[node];
    }
    int mid = (s + e) / 2;
    return tree[node] = init_tree(s, mid, node * 2) + init_tree(mid + 1, e, node * 2 + 1);
}

void init() {
    cin >> N >> M;
    init_tree(0, N - 1, 1);
}

int get_sum(int s, int e, int l, int r, int node) {
    int mid = (s + e) / 2;
    if (l <= s && e <= r) {
        return tree[node];
    }
    if (r < s || e < l)
        return 0;
    return get_sum(s,mid,l,r,node<<1) + get_sum(mid+1,e,l,r,node<<1|1);
}

void solve() {
    int a, b;
    for (int i = 0; i < M; i++) {
        answer = 0;
        cin >> a >> b;
        answer += get_sum(0, N - 1, a - 1, b - 1, 1);
        cout << answer << "\n";
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