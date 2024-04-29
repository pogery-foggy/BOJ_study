#include <iostream>
#include <vector>
#define MAX_N 100000

using namespace std;

int tree[4 * MAX_N];
int arr[MAX_N + 1];
int N, M;

int init_tree(int s, int e, int node) {
    if (s == e) {
        tree[node] = s;
        return tree[node];
    }

    int mid = (s + e) / 2;
    int left = init_tree(s, mid, node << 1);
    int right = init_tree(mid + 1, e, node << 1 | 1);

    tree[node] = arr[left] < arr[right] ? left : right;

    return tree[node];
}

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    init_tree(0, N - 1, 1);
}

int fnd(int s, int e, int left, int right, int node) {
    if (right < s || e < left)
        return -1;
    if (left <= s && e <= right)
        return tree[node];

    int mid = (s + e) >> 1;

    int left_tree = fnd(s, mid, left, right, node << 1);
    int right_tree = fnd(mid + 1, e, left, right, node << 1 | 1);

    if (left_tree == -1)
        return right_tree;
    if (right_tree == -1)
        return left_tree;

    return arr[left_tree] < arr[right_tree] ? left_tree : right_tree;
}

int solve(int s, int e) {
    int m = fnd(0, N - 1, s, e, 1);
    long long answer = (long long)(e - s + 1) * (long long)arr[m];

    if (s <= m - 1) {
        int temp = solve(s, m - 1);
        if (answer < temp)
            answer = temp;
    }
    if (m + 1 <= e) {
        int temp = solve(m + 1, e);
        if (answer < temp)
            answer = temp;
    }
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    cout << solve(0, N - 1);
}