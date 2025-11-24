#include <iostream>
#include <queue>
#include <vector>
#define INF 2147000000
#define MAX_N 50001
using namespace std;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
vector<pair<int, int>> edge[MAX_N];
vector<int> dist(MAX_N, INF);
int N, M;
void init() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        edge[u].push_back({v, c});
        edge[v].push_back({u, c});
    }
}

void solve() {
    pq.push({0, 1});
    while (!pq.empty()) {
        int cur = pq.top().second;
        int distance = pq.top().first;
        pq.pop();
        if (dist[cur] != INF)
            continue;
        dist[cur] = distance;
        for (auto next : edge[cur]) {
            int next_distance = next.second + distance;
            if (dist[next.first] != INF)
                continue;
            pq.push({next_distance, next.first});
        }
    }
    cout << dist[N];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}