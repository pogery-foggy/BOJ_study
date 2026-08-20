#include <iostream>
#include <queue>
#include <vector>
#define MAX_N 10001
using namespace std;
typedef pair<int, pair<int, int>> piii;
priority_queue<piii, vector<piii>, greater<piii>> pq;
int arr[MAX_N], p[MAX_N], mini = 999999999;
int N, P;

void init() {
    cin >> N >> P;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        mini = mini < arr[i] ? mini : arr[i];
        p[i] = i;
    }
    for (int i = 0; i < P; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        pq.push({c * 2 + arr[u] + arr[v], {u, v}});
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

void solve() {
    int cost = 0;
    int cnt = 0;
    while (cnt < N - 1 && !pq.empty()) {
        int c = pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();
        u = find_root(u);
        v = find_root(v);
        if (u == v)
            continue;
        cnt++;
        cost += c;
        union_root(u, v);
    }
    cout << cost + mini;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}