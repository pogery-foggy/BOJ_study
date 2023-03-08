#include <iostream>
#include <vector>
#define MAX_N 100000
using namespace std;

int N, K;
int tree[MAX_N * 4 + 1], arr_index[MAX_N + 1];
vector<int> answer;

int init_tree(int s, int e, int node) {
    if (s == e) {
        arr_index[s + 1] = node;
        return tree[node] = 1;
    }
    int mid = (s + e) >> 1;

    return tree[node] = init_tree(s, mid, node << 1) + init_tree(mid + 1, e, node << 1 | 1);
}
void init() {
    cin >> N >> K;
    init_tree(0, N - 1, 1);
}

void update(int idx) {
    int fnd_node = arr_index[idx]; // 아마 여기오류
    while (fnd_node > 0) {
        tree[fnd_node] -= 1;
        fnd_node >>= 1;
    }
}

int find(int s, int e, int node, int fnd) {
    if (s == e)
        return (s + 1);
    int mid = (s + e) >> 1;
    if (tree[node << 1] >= fnd)
        return find(s, mid, node << 1, fnd);
    else
        return find(mid + 1, e, node << 1 | 1, fnd - tree[node << 1]);
}

void solve() {
    int fnd = K;
    while (tree[1]) {
        int ans = find(0, N - 1, 1, fnd);
        cout << " start " << fnd << "  " << ans << " " << tree[1] << "  end";
        answer.push_back(ans); // fnd-1을 해야하나?
        fnd += K - 1;
        update(ans);
        if(tree[1] == 0) break;
        if (!(fnd % tree[1]))
            fnd = tree[1];
        else if (fnd > tree[1])
            fnd = fnd % (tree[1]);

        for (int i = 1; i < 14; i++)
            cout << tree[i] << " ";
        cout << "\n";
    }

    cout << "<";
    for (int i = 0; i < N - 1; i++) {
        cout << answer[i] << ", ";
    }
    cout << answer[N - 1] << ">";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);
    init();
    solve();
    return 0;
}