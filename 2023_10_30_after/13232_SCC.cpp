#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

stack<int> group;
int check[5001];
vector<vector<int>> groups;
bool is_group[5001];
vector<int> edge[5001];
int num, V, E;

void init() {
    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        int s, e;
        cin >> s >> e;
        edge[s].push_back(e);
    }
}

int dfs(int idx) {
    // check에 방문순서를 넣어주고
    // group에 추가
    // 부모를 현재 노드의 방문순서로
    check[idx] = ++num;
    group.push(idx);
    int parent = check[idx];

    for (auto a : edge[idx]) {
        int child = a;
        if (!check[child]) {
            parent = min(parent, dfs(child));
        } else if (!is_group[child]) {
            parent = min(parent, check[child]);
        }
    }

    // 돌아왔다면
    if (parent == check[idx]) {
        // group만들기
        vector<int> temp;
        // 자기까지만 빼기
        while (true) {
            int cur = group.top();
            is_group[cur] = true;
            temp.push_back(cur);
            group.pop();

            if (cur == idx)
                break;
        }
        groups.push_back(temp);
    }

    return parent;
}

void solve() {
    for (int i = 1; i <= V; i++) {
        if (!check[i])
            dfs(i);
    }
    int maxi = 0;
    for (int i = 0; i < groups.size(); i++) {
        maxi = maxi > groups[i].size() ? maxi : groups[i].size();
    }
    cout << maxi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}