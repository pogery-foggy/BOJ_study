#include <iostream>
#include <queue>
using namespace std;

int N, sx, sy, ex, ey;
bool is_visit[300][300];
int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {1, -1, 2, -2, 2, -2, 1, -1};
void init() {
    cin >> N >> sx >> sy >> ex >> ey;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            is_visit[i][j] = false;
        }
    }
}

bool is_valid(int x, int y) {
    if (x < 0 || x >= N)
        return false;
    if (y < 0 || y >= N)
        return false;
    return true;
}

int bfs() {
    queue<pair<pair<int, int>, int>> q;
    q.push({{sx, sy}, 0});
    is_visit[sx][sy] = true;
    while (!q.empty()) {
        int cur_x = q.front().first.first;
        int cur_y = q.front().first.second;
        int cnt = q.front().second;
        if (cur_x == ex && cur_y == ey)
            return cnt;
        q.pop();
        for (int i = 0; i < 8; i++) {
            int nx = cur_x + dx[i];
            int ny = cur_y + dy[i];
            if (!is_valid(nx, ny))
                continue;
            if (!is_visit[nx][ny]) {
                q.push({{nx, ny}, cnt + 1});
                is_visit[nx][ny] = true;
            }
        }
    }
    return -1;
}

void solve() {
    int answer = bfs();
    cout << answer << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}