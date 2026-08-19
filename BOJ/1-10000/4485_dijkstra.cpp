#include <iostream>
#include <queue>
#include <vector>
#define INF 2100000000

using namespace std;
int N;
int map[126][126];
int dist[126][126];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int from, to, cnt;

void init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            dist[i][j] = INF;
        }
    }
    from = 0;
    to = N - 1;
}

bool is_valid(int x, int y) {
    if (x < 0 || x >= N)
        return false;
    if (y < 0 || y >= N)
        return false;
    return true;
}

void dijkstra(int s) {
    dist[s][s] = INF;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    pq.push({map[s][s], {s, s}});
    while (!pq.empty()) {
        int cost = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        if (dist[x][y] != INF)
            continue;
        dist[x][y] = cost;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!is_valid(nx, ny))
                continue;
            int next_cost = map[nx][ny] + cost;
            if (dist[nx][ny] == INF) {
                pq.push({next_cost, {nx, ny}});
            }
        }
    }
}

void solve() {
    dijkstra(from);
    cout << "Problem " << ++cnt << ": " << dist[to][to] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (1) {
        cin >> N;
        if (!N)
            break;
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}