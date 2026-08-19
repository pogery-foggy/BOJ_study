#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
vector<int> edge[101];
vector<vector<int>> groups;
stack<int> group;
bool is_group[101];
int check[101];
int N, num;
int cost[101];

void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> cost[i];
    }
    for (int s = 1; s <= N; s++) {
        for (int e = 1; e <= N; e++) {
            char user_in;
            cin >> user_in;
            if (user_in - '0') {
                edge[s].push_back(e);
            }
        }
    }
}

int dfs(int idx) {
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

    if (parent == check[idx]) {
        vector<int> temp;
        while (true) {
            int cur = group.top();
            is_group[cur] = true;
            temp.push_back(cost[cur]);
            group.pop();

            if (cur == idx)
                break;
        }
        sort(temp.begin(), temp.end());
        groups.push_back(temp);
    }

    return parent;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        if (!check[i])
            dfs(i);
    }
    int sum = 0;
    for (auto a : groups) {
        sum += a[0];
    }

    cout << sum;
    // sort();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}