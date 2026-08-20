#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#define MAX_N 1001
#define INF 4000000000000000LL
using namespace std;
typedef long long ll;
typedef pair<ll, pair<int, int>> plii;
int N, M, K;
vector<vector<pair<ll, int>>> edge;
long long year = 0;
int start_node, end_node;
vector<vector<long long>> dist(MAX_N, vector<long long>(MAX_N, INF));

void init() {
    cin >> N >> M >> K;
    cin >> start_node >> end_node;
    edge.resize(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        edge[u].push_back({c, v});
        edge[v].push_back({c, u});
    }
}

void dijkstra(long long s, long long e) {
    priority_queue<plii, vector<plii>, greater<plii>> pq; // cost, node, cnt
    dist[s][0] = 0;
    pq.push({0, {s, 0}});
    while (!pq.empty()) {
        ll distance = pq.top().first;
        int cur = pq.top().second.first;
        int cnt = pq.top().second.second;
        pq.pop();
        if (dist[cur][cnt] < distance)
            continue;
        if (cnt == N - 1)
            continue; // 이거 안하면 터짐 간선의 최대 개수를 N-1개라 가정
        for (auto next : edge[cur]) {
            ll ndistance = distance + next.first;
            int ncnt = cnt + 1;
            int nnode = next.second;
            if (dist[nnode][ncnt] <= ndistance)
                continue;
            dist[nnode][ncnt] = ndistance;
            pq.push({ndistance, {nnode, ncnt}});
        }
    }
}

long long fnd(long long added) {
    long long answer = INF;
    for (int i = 0; i < N; i++) {
        if (dist[end_node][i] == INF)
            continue;
        answer = min(answer, dist[end_node][i] + (added * i));
    }
    return answer;
}

void solve() {
    dijkstra(start_node, end_node);
    // cout << dist[end_node][0];
    cout << fnd(0) << "\n";
    for (int i = 0; i < K; i++) {
        int a;
        cin >> a;
        year += a;
        cout << fnd(year) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}