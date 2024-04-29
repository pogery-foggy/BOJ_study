#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> edge[100001];
vector<vector<int>> groups;
stack<int> group;
int what_group[100001];
int check[100001], indegree[100001];
int N, M, num, scc_cnt;

void init() {
    groups.clear();
    num = 0;
    cin >> N >> M;
    scc_cnt = 0;
    for (int i = 1; i <= N; i++) {
        edge[i].clear();
        check[i] = 0;
        what_group[i] = 0;
        indegree[i] = 0;
    }
    for (int i = 0; i < M; i++) {
        int n, m;
        cin >> n >> m;
        edge[n].push_back(m);
    }
}

int dfs(int idx) {
    group.push(idx);
    check[idx] = ++num;
    int parent = check[idx];
    for (auto a : edge[idx]) {
        int child = a;
        if (!check[child])
            parent = min(parent, dfs(child));
        else if (!what_group[child])
            parent = min(parent, check[child]);
        else
            indegree[what_group[child]]++;
    }
    if (parent == check[idx]) {
        scc_cnt++;
        while (true) {
            int cur = group.top();
            what_group[cur] = scc_cnt;
            group.pop();

            if (cur == idx)
                break;
        }
        // 끝났는데도 남아있으면 indegree가 있었다는거
        if (!group.empty())
            indegree[scc_cnt]++;
    }
    return parent;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        if (!check[i])
            dfs(i);
    }

    int answer = 0;
    for (int i = 1; i <= scc_cnt; i++)
        if (!indegree[i]) {
            answer++;
        }
    cout << answer << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}