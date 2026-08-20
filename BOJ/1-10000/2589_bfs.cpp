#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

int map[51][51];
int is_visit[51][51];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int N, M, time = -1;
bool is_valid(int y, int x) {
    if (y < 1 || y > N)
        return false;
    if (x < 1 || x > M)
        return false;
    return true;
}

void init() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            char a;
            cin >> a;
            if (a == 'L')
                map[i][j] = 1;
            else
                map[i][j] = 0;
        }
    }
}

void map_init() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            is_visit[i][j] = 0;
        }
    }
}

int bfs(int y, int x) {
    queue<pair<int, int>> q;
    int maxi = -1;
    q.push({y, x});
    is_visit[y][x] = 1;
    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int ny = cur_y + dy[i];
            int nx = cur_x + dx[i];
            if (!is_valid(ny, nx))
                continue;
            if (!is_visit[ny][nx] && map[ny][nx]) {
                q.push({ny, nx});
                is_visit[ny][nx] = is_visit[cur_y][cur_x] + 1;
                maxi = max(maxi, is_visit[ny][nx]);
            }
        }
    }
    return maxi - 1;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j]) {
                map_init();
                time = max(bfs(i, j), time);
            }
        }
    }
    cout << time;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}