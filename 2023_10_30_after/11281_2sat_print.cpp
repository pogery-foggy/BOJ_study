#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
#define MAX_N 10001

using namespace std;

stack<int> group;
int groups[MAX_N * 2];
vector<int> edge[MAX_N * 2];
int check[MAX_N * 2];
int N, M, num, scc_group_num;
bool is_group[MAX_N * 2];

vector<vector<int>> SCC;
int answer[MAX_N * 2];
bool visit_answer[MAX_N * 2];
// 2sat 두배를 만들고, i+N
void init() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a = a > 0 ? (a << 1) : ((-a) << 1 | 1);
        b = b > 0 ? (b << 1) : ((-b) << 1 | 1);
        edge[a ^ 1].push_back(b);
        edge[b ^ 1].push_back(a);
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
            groups[cur] = scc_group_num;
            group.pop();
            temp.push_back(cur);

            if (cur == idx)
                break;
        }
        SCC.push_back(temp);
        scc_group_num++;
    }
    return parent;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        if (!check[i << 1]) {
            dfs(i << 1);
        }
        if (!check[i << 1 | 1]) {
            dfs(i << 1 | 1);
        }
    }
    for (int i = 1; i <= N; i++) {
        int t = i << 1;
        if (groups[t] == groups[t ^ 1]) {
            cout << 0;
            return;
        }
    }
    cout << 1 << "\n";
    // reverse 쓰지마라 뒤지기싫으면 그래서 reverse안쓰고 [b]=1, [b^1] = 0
    for (auto a : SCC) {
        for (auto b : a) {
            if (!visit_answer[b]) {
                answer[b] = 1;
                answer[b ^ 1] = 0;
                visit_answer[b] = true;
                visit_answer[b ^ 1] = true;
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        cout << answer[i << 1] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}