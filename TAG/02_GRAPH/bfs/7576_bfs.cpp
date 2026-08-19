#include <iostream>
#include <queue>
#include <vector>
using namespace std;

queue<pair<pair<int, int>, int>> q;
int map[1001][1001];
bool visited[1001][1001];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int answer, N, M, map_cnt;

void init() {
    cin >> M >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
}

bool valid(int x, int y) {
    if (x < 0 || x >= N)
        return false;
    if (y < 0 || y >= M)
        return false;
    return true;
}

void bfs() {
    pair<pair<int, int>, int> cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        int x = cur.first.first;
        int y = cur.first.second;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if ((valid(nx, ny)) && (map[nx][ny] == 0) && (!visited[nx][ny])) {
                visited[nx][ny] = true;
                map_cnt++; // queue에 추가할때 cnt++
                q.push({{nx, ny}, cur.second + 1});
                answer = answer > cur.second + 1 ? answer : cur.second + 1;
            }
        }
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == -1) {
                map_cnt++; // -1일때 cnt++
            }
            if (map[i][j] == 1) {
                // 들어올 때 cnt++
                map_cnt++;
                q.push({{i, j}, 0});
                visited[i][j] = true;
            }
        }
    }
    bfs();
    if (map_cnt != N * M)
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