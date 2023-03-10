#include <iostream>
#include <vector>
#define MAX_N 200000
#define DIV 1000000007

using namespace std;
pair<long long, long long> tree[MAX_N * 4]; // 좌표, cnt
int N, x, maxed = 0;
long long answer = 1;

pair<long long, long long> update(int s, int e, int node, int x) {
    if (s > x || e < x)
        return tree[node];
    if (s == e && s == x) {
        tree[node].first += x;
        tree[node].second++;
        return tree[node];
    }
    int mid = (s + e) >> 1;
    pair<long long, long long> left = update(s, mid, node << 1, x);
    pair<long long, long long> right = update(mid + 1, e, node << 1 | 1, x);
    return tree[node] = {left.first + right.first, left.second + right.second};
}

void init() {
    cin >> N;
    int tree_first;
    cin >> tree_first;
    update(0, 199999, 1, tree_first);
}

pair<long long, long long> get_left(int s, int e, int fnd, int node) {
    if (e < fnd)
        return tree[node];
    if (fnd <= s)
        return {0, 0};
    int mid = (s + e) >> 1;
    pair<long long, long long> left = get_left(s, mid, x, node << 1);
    pair<long long, long long> right = get_left(mid + 1, e, x, node << 1 | 1);
    return {left.first + right.first, left.second + right.second};
}

pair<long long, long long> get_right(int s, int e, int fnd, int node) {
    if (s > fnd)
        return tree[node];
    if (fnd >= e)
        return {0, 0};
    int mid = (s + e) >> 1;
    pair<long long, long long> left = get_right(s, mid, x, node << 1);
    pair<long long, long long> right = get_right(mid + 1, e, x, node << 1 | 1);
    return {left.first + right.first, left.second + right.second};
}
void solve() {
    pair<long long, long long> le, ri;
    long long l, r;
    for (int i = 2; i <= N; i++) {
        cin >> x;                        // x가 maxed보다 크면 예외처리 해야하나?
        le = get_left(0, 199999, x, 1);  // -2?
        ri = get_right(0, 199999, x, 1); //
        l = le.second * x - le.first;
        r = ri.first - (ri.second * x);
        update(0, 199999, 1, x);

        answer *= ((le.second * x - le.first) + (ri.first - (ri.second * x))) % DIV;
        answer %= DIV;
    }
    // 왼쪽나무의 수 * 자신의 좌표 - (왼쪽의 있는 나무들의 좌표)
    //(오른쪽 나무들의 좌표) - (오른쪽 나무의 수 * 자신의 좌표)
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    if (tree[1].second == 1) {
        cout << 0;
    } else {
        cout << answer;
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}