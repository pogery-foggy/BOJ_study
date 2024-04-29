#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
#define MAX_N 1001

using namespace std;

stack<int> group;
int groups[MAX_N * 2];
vector<int> edge[MAX_N * 2];
int check[MAX_N * 2];
int num, scc_group_num;
bool is_group[MAX_N * 2];
vector<vector<int>> SCC;
int answer[MAX_N * 2];
bool visit_answer[MAX_N * 2];
int N, M;

void init() {
    for (int i = 1; i <= N; i++) {
        edge[i].clear();
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a = a > 0 ? (a << 1) : ((-a) << 1 | 1);
        b = b > 0 ? (b << 1) : ((-b) << 1 | 1);
        edge[a ^ 1].push_back(b);
        edge[b ^ 1].push_back(a);
    }
}

void solve() {}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> N >> M) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}