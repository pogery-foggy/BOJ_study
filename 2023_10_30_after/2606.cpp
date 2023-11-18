#include <iostream>

using namespace std;
int arr[101][101];
bool visit[101];
int cnt, n, edgy;
void init() {
    cin >> n;
    cin >> edgy;
    for (int i = 0; i < edgy; i++) {
        int a, b;
        cin >> a >> b;
        arr[a][b] = 1;
        arr[b][a] = 1;
    }
    cnt = -1;
}

void dfs(int fnd) {
    cnt++;
    visit[fnd] = true;
    for (int i = 1; i <= n; i++) {
        if (visit[i])
            continue;
        if (!arr[fnd][i])
            continue;
        dfs(i);
    }
}

void solve() {
    dfs(1);
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}