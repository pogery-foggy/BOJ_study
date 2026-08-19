#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N, M;
char map[21][21];
bool char_visit[26];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int maxi = 0;

bool is_valid(int y, int x) {
    if (x < 0 || x >= M)
        return false;
    if (y < 0 || y >= N)
        return false;
    return true;
}

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
}

void dfs(int y, int x, int cnt) {
    char cur = map[y][x];
    maxi = max(cnt, maxi);
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (!is_valid(ny, nx))
            continue;
        if (!char_visit[map[ny][nx]-'A']) {
            char_visit[map[ny][nx]-'A'] = true;
            dfs(ny, nx, cnt + 1);
            char_visit[map[ny][nx]-'A'] = false;
        }
    }
}

void solve() {
    char_visit[map[0][0] - 'A'] = true;
    dfs(0, 0, 1);
    cout << maxi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}