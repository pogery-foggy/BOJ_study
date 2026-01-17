#include <iostream>
#include <queue>
using namespace std;
typedef pair<int, pair<int, int>> piii;
int N, map[15][15], sx, sy, ex, ey;
int is_visit[15][15];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
void init() {
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            is_visit[i][j] = false;
        }
    cin >> sy >> sx >> ey >> ex;
}

bool is_valid(int y, int x) {
    if (x < 0 || N <= x)
        return false;
    if (y < 0 || N <= y)
        return false;
    return true;
}

int bfs(int y, int x) {
    priority_queue<piii, vector<piii>, greater<piii>> q;
    q.push({0, {sy, sx}});
    is_visit[sy][sx] = true;
    while (!q.empty()) {
        int cur_y = q.top().second.first;
        int cur_x = q.top().second.second;
        int cnt = q.top().first;
        q.pop();
        if (cur_x == ex && cur_y == ey)
            return cnt;
        for (int i = 0; i < 4; i++) {
            int ny = cur_y + dy[i];
            int nx = cur_x + dx[i];
            if (!is_valid(ny, nx))
                continue;
            if (map[ny][nx] == 1)
                continue;
            if (is_visit[ny][nx])
                continue;
            if (map[ny][nx] == 2) {
                q.push({(cnt / 3 + 1) * 3, {ny, nx}});
            } else {
                q.push({cnt + 1, {ny, nx}});
            }
            is_visit[ny][nx] = true;
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 1; testcase <= T; testcase++) {
        init();
        cout << "#" << testcase << " " << bfs(sy, sx) << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}