#include <iostream>
#define MAX_SIZE 100001
using namespace std;

int answer, n, q, mode;
int seg_tree[4 * MAX_SIZE], arr[MAX_SIZE];

int tree_init(int node, int start, int end) {
    // node번째 노드는  start~end 합
    if (start == end)
        return seg_tree[node] = arr[start];
    int middle = (start + end) / 2;

    return seg_tree[node] = tree_init(node * 2, start, middle) + tree_init(node * 2 + 1, middle + 1, end);
}

void update(int node, int start, int end, int idx, int diff) {
    if (start <= idx && idx <= end)
        seg_tree[node] += diff;
    else
        return;

    int middle = (start + end) / 2;
    update(node * 2, start, middle, idx, diff);
    update(node * 2 + 1, middle + 1, end, idx, diff);
}

int sum(int l, int r, int node, int st, int end) {
    // st   : 시작 인덱스
    // end  : 끝 인덱스
    // l~r  : 구하고자 하는 구간 합의 범위

    // [l, r]이 [st, end]를 완전히 포함하는 경우
    if (l <= st && end <= r)
        return seg_tree[node];

    // [l, r]와 [st, end]가 겹치지 않는 경우
    if (r < st || end < l)
        return 0;

    // 나머지 경우 (일부분 겹칠때)
    int m = (st + end) / 2;
    return sum(l, r, node * 2, st, m) + sum(l, r, node * 2 + 1, m + 1, end);
}

void init() {
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void solve() {
    for (int i = 0; i < q; i++) {
        cin >> mode;
        if (mode) {
            answer = 0;
            int left, right;
            cin >> left >> right;

        } else {
            int idx, x;
            cin >> idx >> x;
            update(1, 0, n - 1, idx, x - arr[idx]);
        }
    }
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        init();
        cout << "#" << test_case << " ";
        solve();
        cout << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}