#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<vector<int>> edgy;
bool visited[1001];
int N, M, start;

void init() {
    cin >> N >> M >> start;
    edgy.resize(N + 1);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        edgy[a].push_back(b);
        edgy[b].push_back(a);
    }
    for (int i = 1; i <= N; i++) {
        sort(edgy[i].begin(), edgy[i].end());
    }
}

void dfs(int cur) {
    if (visited[cur])
        return;
    visited[cur] = true;
    cout << cur << " ";
    for (auto a : edgy[cur]) {
        dfs(a);
    }
}

void bfs(int s) {
    for (int i = 1; i <= N; i++) {
        visited[i] = false;
    }
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << cur << " ";
        for (auto a : edgy[cur]) {
            if (!visited[a]) {
                visited[a] = true;
                q.push(a);
            }
        }
    }
}
void solve() {
    dfs(start);
    cout << "\n";
    bfs(start);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}