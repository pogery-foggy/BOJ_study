#include <iostream>
#include <queue>
#include <utility>
using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
queue<pair<pair<int, int>, int>> q;
int map[1001][1001];
bool visited[1001][1001];
int N, M;

bool is_valid(int x, int y) {
    if (x < 0 || x >= N)
        return false;
    if (y < 0 || y >= M)
        return false;
    return true;
}

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] == 2) {
                q.push({{i, j}, 0});
                visited[i][j] = true;
            }
        }
    }
}
void bfs() {
    while (!q.empty()) {
        pair<pair<int, int>, int> cur = q.front();
        map[cur.first.first][cur.first.second] = cur.second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = dx[i] + cur.first.first;
            int ny = dy[i] + cur.first.second;
            if (is_valid(nx, ny) && !visited[nx][ny] && map[nx][ny]) {
                q.push({{nx, ny}, cur.second + 1});
                visited[nx][ny] = true;
            }
        }
    }
}

void solve() {
    bfs();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (visited[i][j])
                cout << map[i][j] << " ";
            else {
                if (map[i][j] == 0)
                    cout << "0 ";
                else
                    cout << "-1 ";
            }
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}