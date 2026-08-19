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
        while (true) {
            int cur = group.top();
            is_group[cur] = true;
            groups[cur] = scc_group_num;
            group.pop();

            if (cur == idx)
                break;
        }
        scc_group_num++;
    }
    return parent;
}

int solve() {
    for (int i = 1; i <= 2 * N; i++) {
        if (!check[i]) {
            dfs(i);
        }
    }
    for(int i = 1; i <= N; i++){
        int t = i<<1;
        if(groups[t]==groups[t^1]){
            return 0;
        }
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    cout << solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}