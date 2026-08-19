#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<vector<int>> edgy;
bool visited[1001];
int N, M, cnt;

void init() {
    cin >> N >> M;
    edgy.resize(N + 1);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        edgy[a].push_back(b);
        edgy[b].push_back(a);
    }
}

void bfs(int s) {
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto a : edgy[cur]) {
            if (!visited[a]) {
                q.push(a);
                visited[a] = true;
            }
        }
    }
}

void solve() {
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            cnt++;
            bfs(i);
        }
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}