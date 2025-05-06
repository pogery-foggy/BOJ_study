#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int people[11];
bool selected[11];
int member[2];
int answer = 2100000000;
int N;
vector<vector<int>> edge;

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> people[i];
    }
    edge.resize(N);
    for (auto &ed : edge) {
        int a;
        cin >> a;
        ed.resize(a);
        for (auto &b : ed) {
            int x;
            cin >> x;
            b = x - 1;
        }
    }
}

bool bfs(bool group) {
    vector<bool> is_visit(N, false);
    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (selected[i] == group) {
            q.push(i);
            is_visit[i] = true;
            break;
        }
    }
    int cnt = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cnt++;
        for (auto n : edge[cur]) {
            if (is_visit[n])
                continue;
            if (selected[n] == group) {
                is_visit[n] = true;
                q.push(n);
            }
        }
    }

    int total = 0;
    for (int i = 0; i < N; i++) {
        if (selected[i] == group) {
            member[group] += people[i];
            total++;
        }
    }
    return (cnt == total);
}

void selects(int cnt, int index, int K) {
    if (cnt == K) {
        member[true] = 0;
        member[false] = 0;
        if (bfs(true) && bfs(false)) {
            answer = min(answer, abs(member[true] - member[false]));
        }
        return;
    }
    for (int i = index; i < N; i++) {
        selected[i] = true;
        selects(cnt + 1, i + 1, K);
        selected[i] = false;
    }
}

void solve() {
    for (int k = 1; k <= N - 1; k++) {
        selects(0, 0, k);
    }
    if (answer == 2100000000)
        cout << -1;
    else
        cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}