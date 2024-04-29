#include <iostream>
#include <queue>
#include <vector>
#define INF 2100000000
using namespace std;

vector<pair<int, int>> edge[1001];
vector<pair<int, int>> reverse_edge[1001];
vector<int> dist(1001, INF);
vector<int> reverse_dist(1001, INF);
int N, M, x;
void init() {
    cin >> N >> M;
    cin >> x;
    // 역방향
    for (int i = 0; i < M; i++) {
        int s, e, v;
        cin >> s >> e >> v;
        edge[s].push_back({e, v});
        reverse_edge[e].push_back({s, v});
    }
}

void dijkstra() {
    dist[x] = INF;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, x});
    while (!pq.empty()) {
        int cur = pq.top().second;
        int distance = pq.top().first;
        pq.pop();

        if (dist[cur] != INF)
            continue;
        dist[cur] = distance;

        for (auto next : edge[cur]) {
            int next_dist = next.second + distance;
            if (dist[next.first] == INF) {
                pq.push({next_dist, next.first});
            }
        }
    }
}

void reverse_dijkstra() {
    reverse_dist[x] = INF;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, x});
    while (!pq.empty()) {
        int cur = pq.top().second;
        int distance = pq.top().first;
        pq.pop();

        if (reverse_dist[cur] != INF)
            continue;
        reverse_dist[cur] = distance;

        for (auto next : reverse_edge[cur]) {
            int next_dist = next.second + distance;
            if (reverse_dist[next.first] == INF) {
                pq.push({next_dist, next.first});
            }
        }
    }
}

void solve() {
    dijkstra();
    reverse_dijkstra();
    int answer = -1;
    for (int i = 1; i <= N; i++) {
        if (i == x)
            continue;
        answer = max(answer, reverse_dist[i] + dist[i]);
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}