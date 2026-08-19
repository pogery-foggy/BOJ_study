#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 100001
using namespace std;

int V, E;
vector<int> edge[MAX_N];
int visited[MAX_N]; // 방문 순서
int up_limit[MAX_N]; // 역으로 타고 올라 갈 수 있는 한계
bool is_cut[MAX_N];
int depth, cnt;

void init() {
    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
}

// 타잔 
// 단절점 -> 루트는 자식이 두개면 단절점
int dfs(int cur, int parent) {
    // 1 2 3 4 그리고 4 2를 생각하면서 보면 이해 됨.
    visited[cur] = up_limit[cur] = ++depth;

    int child = 0;
    for (int nxt : edge[cur]) {
        if (nxt == parent) continue; // 사실상 nxt != prev임

        if (visited[nxt] == 0) { // 방문 안한점일경우
            child++;
            int ret = dfs(nxt, cur);
            up_limit[cur] = min(up_limit[cur], ret); // 중간애들도 물들이기

            // 중요!!! nxt 즉 ret이 cur의 조상으로 올라갈 수 없으면
            // cur을 제거하면 ret이 cur 위로 못 가는 거니까 단절점임.
            if (parent != 0 && ret >= visited[cur]) {
                is_cut[cur] = true;
            }
        } else {  // nxt를 방문했으면, nxt는 오래전 노드임
            up_limit[cur] = min(up_limit[cur], visited[nxt]);  
        }
    }

    if (parent == 0 && child >= 2) { // 루트노드는 자식이 두개면 단절점
        is_cut[cur] = true;
    }
    return up_limit[cur]; 
}

void solve() {
    for (int i = 1; i <= V; i++) {
        if (visited[i] == 0) dfs(i, 0);
    }

    for (int i = 1; i <= V; i++) {
        if (is_cut[i]) cnt++;
    }
    cout << cnt << "\n";
    for (int i = 1; i <= V; i++) {
        if (is_cut[i]) cout << i << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}
