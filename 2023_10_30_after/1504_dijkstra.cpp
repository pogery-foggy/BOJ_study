#include <iostream>
#include <queue>
#include <vector>
#define INF 2100000000
using namespace std;

vector<pair<int, int>> edge[801];
int N, M;
int v1, v2;
void init() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int s, e, v;
        cin >> s >> e >> v;
        edge[s].push_back({e, v});
        edge[e].push_back({s, v});
    }
    cin >> v1 >> v2;
}

int dijkstra(int s, int e) {
    vector<int> dist(801, INF);
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({dist[s], s});

    while (!pq.empty()) {
        int cur = pq.top().second;
        int distance = pq.top().first;
        pq.pop();

        // ? 방문체크?
        if (distance > dist[cur])
            continue;

        for (auto next : edge[cur]) {
            // next.first 다음탐색
            int next_dist = next.second + distance;

            if (next_dist < dist[next.first]) {
                dist[next.first] = next_dist;
                pq.push({next_dist, next.first});
            }
        }
    }
    return dist[e];
}

void solve() {
    int res1, res2;
    int a1 = dijkstra(1, v1);
    int a2 = dijkstra(v1, v2);
    int a3 = dijkstra(v2, N);
    if (a1 == INF || a2 == INF || a3 == INF)
        res1 = INF;
    else
        res1 = a1 + a2 + a3;
    int b1 = dijkstra(1, v2);
    int b2 = dijkstra(v2, v1);
    int b3 = dijkstra(v1, N);
    if (b1 == INF || b2 == INF || b3 == INF)
        res2 = INF;
    else
        res2 = b1 + b2 + b3;

    if (res1 == INF && res2 == INF)
        cout << -1;
    else
        cout << min(res1, res2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}