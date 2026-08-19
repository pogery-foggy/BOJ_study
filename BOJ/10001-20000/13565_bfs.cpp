#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// M 세로 N 가로
int N, M;
int map[1001][1001];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
bool is_visit[1001][1001];

void init() {
    cin >> M >> N;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            char a;
            cin >> a;
            map[i][j] = a - '0';
        }
    }
}

bool is_valid(int x, int y) {
    if (x < 0 || x >= N)
        return false;
    if (y < 0 || y >= M)
        return false;
    return true;
}

bool bfs(int y, int x) {
    queue<pair<int, int>> q;
    q.push({y, x});
    is_visit[y][x] = true;
    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        if (cur_y == M - 1)
            return true;

        for (int i = 0; i < 4; i++) {
            int nx = cur_x + dx[i];
            int ny = cur_y + dy[i];
            if (!is_valid(nx, ny)) {
                continue;
            }
            if (map[ny][nx] == 0 && !is_visit[ny][nx]) {
                q.push({ny, nx});
                is_visit[ny][nx] = true;
            }
        }
    }
    return false;
}

string solve() {
    for (int i = 0; i < N; i++) {
        if (!map[0][i] && !is_visit[0][i]) {
            bool flag = bfs(0, i);
            if (flag == true)
                return "YES";
        }
    }
    return "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    cout << solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}
