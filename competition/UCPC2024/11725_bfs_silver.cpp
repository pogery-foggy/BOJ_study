#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N;
vector<vector<int>> edge;
bool visited[100001];
int parent[100001];

void init() {
    cin >> N;
    edge.resize(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
}

void bfs(int s) {
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto a : edge[cur]) {
            if (!visited[a]) {
                q.push(a);
                visited[a] = true;
                parent[a] = cur;
            }
        }
    }
}

void solve() {
    bfs(1);
    for (int i = 2; i <= N; i++) {
        cout << parent[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}