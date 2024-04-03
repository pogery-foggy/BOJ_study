#include <iostream>

using namespace std;

char map[51][51];
bool visited[51][51];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int N, M;
void init() {
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
}

bool is_valid(int x, int y) {
    if (y < 0 || y >= N)
        return false;
    if (x < 0 || x >= M)
        return false;
    return true;
}

void dfs(int y, int x) {
    visited[y][x] = true;
    char cur = map[y][x];
    if (cur == '-') {
        for (int i = 0; i < 2; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (is_valid(nx, ny) && !visited[ny][nx]) {
                if (map[ny][nx] == map[y][x]) {
                    dfs(ny, nx);
                }
            }
        }
    } else {
        for (int i = 2; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (is_valid(nx, ny) && !visited[ny][nx]) {
                if (map[ny][nx] == map[y][x]) {
                    dfs(ny, nx);
                }
            }
        }
    }
}

void solve() {
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!visited[i][j]) {
                cnt++;
                dfs(i, j);
            }
        }
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}