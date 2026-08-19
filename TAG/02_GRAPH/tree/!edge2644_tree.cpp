#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<vector<int>> edge;
bool is_visit[101];
int N, M, s, e;

void init() {
    cin >> N >> s >> e >> M;
    edge.resize(N + 1);
    for (int i = 0; i < M; i++) {
        int p, c;
        cin >> p >> c;
        edge[p].push_back(c);
        edge[c].push_back(p);
    }
}

int bfs() {
    queue<pair<int, int>> q;
    q.push({s, 0});
    is_visit[s] = true;
    while (!q.empty()) {
        int cur = q.front().first;
        int idx = q.front().second;
        q.pop();
        if (cur == e)
            return idx;
        for (auto a : edge[cur]) {
            if (!is_visit[a]) {
                q.push({a, idx + 1});
                is_visit[a] = true;
            }
        }
    }
    return -1;
}

void solve() { cout << bfs(); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}