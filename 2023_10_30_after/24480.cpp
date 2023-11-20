#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> edgy;
bool visit[100001];
int idx[100001];
int N, M, start,depth;

bool compare(int a, int b) { return a > b; }

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
        sort(edgy[i].begin(), edgy[i].end(), compare);
    }
    depth = 1;
}
void dfs(int cur) {
    visit[cur] = true;
    idx[cur] = depth++;
    for (auto next : edgy[cur]) {
        if (!visit[next])
            dfs(next);
    }
}
void solve() {
    dfs(start);
    for (int i = 1; i <= N; i++) {
        cout << idx[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}