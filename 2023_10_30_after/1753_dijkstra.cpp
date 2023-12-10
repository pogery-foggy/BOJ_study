#include <iostream>
#include <queue>
#include <vector>
#define INF 2100000000
using namespace std;

vector<pair<int, int>> edge[20001];
vector<int> dist(20001, INF);
int N, M, s;
void init() {
    cin >> N >> M;
    cin >> s;
    for (int i = 0; i < M; i++) {
        int s, e, v;
        cin >> s >> e >> v;
        edge[s].push_back({e, v});
    }
}

void dijkstra() {
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
            int next_dist = next.second + distance;
            if (dist[next.first] > next_dist) {
                dist[next.first] = next_dist;
                pq.push({next_dist, next.first});
            }
        }
    }
}

void solve() {
    dijkstra();
    for (int i = 1; i <= N; i++) {
        if (dist[i] == INF)
            cout << "INF\n";
        else
            cout << dist[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}