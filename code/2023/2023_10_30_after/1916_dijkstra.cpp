#include <iostream>
#include <queue>
#include <vector>
#define INF 2100000000
using namespace std;

vector<pair<int, int>> edge[1001];
vector<int> dist(1001, INF);
int N, M;
int from, to;
void init() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int s, e, v;
        cin >> s >> e >> v;
        edge[s].push_back({e, v});
    }
    cin >> from >> to;
}

void dijkstra(int s) {
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({dist[s], s});

    while (!pq.empty()) {
        int cur = pq.top().second;
        int distance = pq.top().first;
        pq.pop();

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
}

void solve() {
    dijkstra(from);
    cout << dist[to];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}