#include <iostream>
#include <queue>
#include <vector>
#define MAX_N 1001
using namespace std;
typedef pair<int, pair<int, int>> piii;
int p[MAX_N];
priority_queue<piii, vector<piii>, greater<piii>> b, r;
int N, M, K;

void init() {
    while (!b.empty())
        b.pop();
    while (!r.empty())
        r.pop();
    for (int i = 0; i < N; i++)
        p[i] = i;
    for (int i = 0; i < M; i++) {
        char color;
        int u, v;
        cin >> color >> u >> v;
        if (color == 'B') {
            b.push({0, {u, v}});
            r.push({1, {u, v}});
        } else {
            b.push({1, {u, v}});
            r.push({0, {u, v}});
        }
    }
}

int find_root(int x) {
    if (p[x] == x)
        return x;
    return p[x] = find_root(p[x]);
}

void union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    p[b] = a;
}

int r_mst() { // 파랑 노드 개수 리턴
    int cost_k = 0;
    int cnt = 0;
    while (cnt < N - 1 && !r.empty()) {
        int c = r.top().first;
        int u = r.top().second.first;
        int v = r.top().second.second;
        r.pop();
        u = find_root(u);
        v = find_root(v);
        if (u == v)
            continue;

        cnt++;
        cost_k += c;
        union_root(u, v);
    }
    return cost_k;
}

int b_mst() { // 빨간 노드 개수 리턴
    int cost_k = 0;
    int cnt = 0;
    while (cnt < N - 1 && !b.empty()) {
        int c = b.top().first;
        int u = b.top().second.first;
        int v = b.top().second.second;
        b.pop();
        u = find_root(u);
        v = find_root(v);
        if (u == v)
            continue;

        cnt++;
        cost_k += c;
        union_root(u, v);
    }
    return cost_k;
}

int solve() {
    int min_K = r_mst();
    for (int i = 0; i < N; i++)
        p[i] = i;
    int max_K = N - 1 - b_mst();
    if (min_K <= K && K <= max_K)
        return 1;
    else
        return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (1) {
        cin >> N >> M >> K;
        if (!N && !M && !K)
            break;
        init();
        cout << solve() << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}