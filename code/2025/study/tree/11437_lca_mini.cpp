#include <iostream>
#include <vector>
#define MAX_N 50001
using namespace std;

int p[MAX_N], depth[MAX_N], N, a, b;
vector<int> edges[MAX_N];
// vector<vector<int>> 후 resize하거나 이런식으로

void dfs(int cur) { // 깊이 구하기
    for (auto next : edges[cur]) {
        if (depth[next] != -1)
            continue; // 이미 구해져있다면
        depth[next] = depth[cur] + 1;
        p[next] = cur;
        dfs(next);
    }
}

void init() {
    cin >> N;
    for(int i = 1; i <= N; i++){
        depth[i] = -1;
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    depth[1] = 0;
    dfs(1);
}

void solve() {
    // 높이 맞추기
    int a, b;
    cin >> a >> b;
    if (depth[a] < depth[b]) { // 더 낮은 위치에 a넣기
        int temp = a;
        a = b;
        b = temp;
    }
    while (depth[a] != depth[b]) {
        a = p[a];
    }
    while (a != b) {
        a = p[a];
        b = p[b];
    }
    cout << a << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}