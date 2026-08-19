#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int p[100000];
int N, Q;
pair<int, pair<int, int>> arr[200000];

void init() {
    cin >> N >> Q;
    for (int i = 0; i < N * 2; i += 2) {
        int _;
        cin >> arr[i].first >> arr[i + 1].first >> _;
        arr[i].second = {-1, i / 2 + 1};
        arr[i + 1].second = {1, i / 2 + 1};
        p[i / 2 + 1] = i / 2 + 1;
    }
    sort(arr, arr + N * 2);
}

int find_root(int x) {
    if (p[x] == x)
        return p[x];
    else
        return p[x] = find_root(p[x]);
}

void union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    p[a] = b;
}

int are_union(int a, int b) { return (find_root(a) == find_root(b) ? 1 : 0); }
void solve() {
    int st = 0, node = 0;
    for (int i = 0; i < N * 2; i++) {
        // cout << "{" << arr[i].first << ",{" << arr[i].second.first << "," << arr[i].second.second << "}\n";
        int cur = arr[i].second.second;
        if (st == 0) {
            node = cur;
        }
        st -= arr[i].second.first;
        if (st != 0 && cur != node) {
            int a = find_root(cur);
            int b = find_root(node);
            if (a != b)
                union_root(a, b);
        }
    }

    for (int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        cout << are_union(a, b) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}