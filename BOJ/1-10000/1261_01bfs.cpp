#include <deque>
#include <iostream>
#include <vector>

using namespace std;

// M 세로 N 가로
int N, M;
int map[101][101];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int visit[101][101];

void init() {
    cin >> M >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char a;
            cin >> a;
            map[i][j] = a - '0';
        }
    }
}

bool is_valid(int x, int y) {
    if (x < 0 || x >= M)
        return false;
    if (y < 0 || y >= N)
        return false;
    return true;
}

int bfs(int y, int x) {
    deque<pair<int, int>> dq;
    dq.push_back({y, x});
    visit[y][x] = 1;
    while (!dq.empty()) {
        int y = dq.front().first;
        int x = dq.front().second;
        dq.pop_front();

        if (y == N - 1 && x == M - 1)
            return visit[N - 1][M - 1] - 1;

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (!is_valid(nx, ny)) {
                continue;
            }
            if (!map[ny][nx] && !visit[ny][nx]) {
                dq.push_front({ny, nx});
                visit[ny][nx] = visit[y][x];
            }
            if (map[ny][nx] && !visit[ny][nx]) {
                dq.push_back({ny, nx});
                visit[ny][nx] = visit[y][x] + 1;
            }
        }
    }
}

void solve() { cout << bfs(0, 0); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}