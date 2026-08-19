#include <iostream>
#include <queue>
using namespace std;

int w, h;
int map[52][52];
bool is_visit[52][52];
int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
int dy[] = {1, -1, 0, 0, -1, 1, 1, -1};

void init() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> map[i][j];
            is_visit[i][j] = false;
        }
    }
}

bool is_valid(int x, int y) {
    if (0 > x || h <= x)
        return false;
    if (0 > y || w <= y)
        return false;
    return true;
}

void bfs(int x, int y) {
    queue<pair<int, int>> q;
    q.push({x, y});
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        for (int i = 0; i < 8; i++) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if (!is_valid(nx, ny))
                continue;
            if (!is_visit[nx][ny] && map[nx][ny]) {
                q.push({nx, ny});
                is_visit[nx][ny] = true;
            }
        }
    }
}

void solve() {
    int cnt = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (!is_visit[i][j] && map[i][j]) {
                bfs(i, j);
                cnt++;
            }
        }
    }
    cout << cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (1) {
        cin >> w >> h;
        if (!w && !h)
            break;
        init();
        solve();
    }
    return 0;
}