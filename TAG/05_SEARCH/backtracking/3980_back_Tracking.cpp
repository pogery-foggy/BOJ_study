#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int player[12][12];
bool is_visit[12];
vector<vector<int>> stat_list(12);
int maxi;

void init() {
    for (int i = 0; i < 11; i++) {
        stat_list[i].clear();
        is_visit[i] = false;
    }
    maxi = 0;
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            cin >> player[i][j];
            if (player[i][j])
                stat_list[j].push_back(i);
        }
    }
}

void dfs(int stat, int total) {
    if (stat == 11) {
        maxi = max(maxi, total);
        return;
    }
    for (int i = 0; i < stat_list[stat].size(); i++) {
        int cur_num = stat_list[stat][i];
        if (player[cur_num][stat] == 0)
            continue;
        if (is_visit[cur_num])
            continue;
        is_visit[cur_num] = true;
        total += player[cur_num][stat];
        dfs(stat + 1, total);
        is_visit[cur_num] = false;
        total -= player[cur_num][stat];
    }
}

void solve() {
    dfs(0, 0);
    cout << maxi << "\n";
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