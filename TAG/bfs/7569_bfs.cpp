#include <iostream>
#include <queue>
#include <vector>
using namespace std;

queue<pair<pair<int, int>, pair<int, int>>> q;
int map[101][101][101];
bool visited[101][101][101];
int dx[] = {0, 0, 1, -1, 0, 0};
int dy[] = {1, -1, 0, 0, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};
int answer, N, M, H, map_cnt;

void init() {
    cin >> M >> N >> H;
    for (int k = 0; k < H; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> map[i][j][k];
            }
        }
    }
}

bool valid(int x, int y, int z) {
    if (x < 0 || x >= N)
        return false;
    if (y < 0 || y >= M)
        return false;
    if (z < 0 || z >= H)
        return false;
    return true;
}

void bfs() {
    pair<pair<int, int>, pair<int, int>> cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        int x = cur.first.first;
        int y = cur.first.second;
        int z = cur.second.first;
        for (int i = 0; i < 6; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];
            if ((valid(nx, ny, nz)) && (map[nx][ny][nz] == 0) && (!visited[nx][ny][nz])) {
                visited[nx][ny][nz] = true;
                map_cnt++; // queue에 추가할때 cnt++
                q.push({{nx, ny}, {nz, cur.second.second + 1}});
                answer = answer > cur.second.second + 1 ? answer : cur.second.second + 1;
            }
        }
    }
}

void solve() {
    for (int k = 0; k < H; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (map[i][j][k] == -1) {
                    map_cnt++; // -1일때 cnt++
                }
                if (map[i][j][k] == 1) {
                    // 들어올 때 cnt++
                    map_cnt++;
                    q.push({{i, j}, {k, 0}});
                    visited[i][j][k] = true;
                }
            }
        }
    }
    bfs();
    if (map_cnt != N * M*H)
        cout << -1;
    else
        cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}