#include <iostream>
#include <vector>
#define MAX_N 100000

using namespace std;

pair<long long, long long> tree[4 * MAX_N];
long user_in;
int N, M;

pair<long long, long long> init_tree(int s, int e, int node) {
    if (s == e) {
        cin >> user_in;
        tree[node] = {user_in, user_in};
        return tree[node];
    }

    int mid = (s + e) / 2;
    pair<long long, long long> left = init_tree(s, mid, node << 1);
    pair<long long, long long> right = init_tree(mid + 1, e, node << 1 | 1);
    tree[node].first = min(left.first, right.first);
    tree[node].second = max(left.second, right.second);

    return tree[node];
}

void init() {
    cin >> N >> M;
    init_tree(0, N - 1, 1);
}

pair<long long, long long> fnd(int s, int e, int left, int right, int node) {
    if (right < s || e < left)
        return {-1, -1};
    if (left <= s && e <= right)
        return tree[node];

    int mid = (s + e) >> 1;

    pair<long long, long long> left_tree = fnd(s, mid, left, right, node << 1);
    pair<long long, long long> right_tree = fnd(mid + 1, e, left, right, node << 1 | 1);

    if (left_tree.first == -1)
        return right_tree;
    if (right_tree.first == -1)
        return left_tree;

    return {min(left_tree.first, right_tree.first), max(left_tree.second, right_tree.second)};
}

void solve() {
    int from, to;
    for (int i = 0; i < M; i++) {
        cin >> from >> to;
        pair<long long, long long> answer = fnd(0, N - 1, from - 1, to - 1, 1);
        cout << answer.first << " " << answer.second << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    solve();
}