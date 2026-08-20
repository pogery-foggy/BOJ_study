#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> edgy;
bool visit[2001], answer;
int start, N, M;
void init() {
    cin >> N >> M;
    start = 1;
    edgy.resize(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        edgy[a].push_back(b);
        edgy[b].push_back(a);
    }
}

void dfs(int cur, int depth) {
    if (depth == 5 || answer) {
        answer = true;
        return;
    }
    visit[cur] = true;
    for (auto next : edgy[cur]) {
        if (!visit[next])
            dfs(next, depth + 1);
    }
    visit[cur] = false;
}

void solve() {
    for (int i = 0; i < N; i++) {
        dfs(i, 1);
        if (answer)
            break;
    }
    cout << answer ? 1 : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}