#include <cmath>
#include <iostream>
#include <queue>
using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int N, L, R;
int map[101][101];
int group[10001];
int is_visit[101][101];
int group_num;
int flag = 0;
bool is_valid(int y, int x) {
    if (y < 0 || y >= N)
        return false;
    if (x < 0 || x >= N)
        return false;
    return true;
}

void init() {
    cin >> N >> L >> R;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
}

bool flip(int n) {
    if (L <= n && n <= R)
        return true;
    else
        return false;
}

void bfs(int y, int x, int g) {
    queue<pair<int, int>> q;
    q.push({y, x});
    int sum = 0, cnt = 0;
    is_visit[y][x] = g;
    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        cnt++;
        sum += map[cur_y][cur_x];
        q.pop();
        for (int i = 0; i < 4; i++) {
            int ny = cur_y + dy[i];
            int nx = cur_x + dx[i];
            if (!is_valid(ny, nx))
                continue;
            if (!is_visit[ny][nx] && flip(abs(map[cur_y][cur_x] - map[ny][nx]))) {
                q.push({ny, nx});
                is_visit[ny][nx] = g;
            }
        }
    }
    group[g] = int(sum / cnt);
}
void map_init() {
    for (int i = 1; i <= group_num; i++)
        group[i] = 0;
    group_num = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            is_visit[i][j] = false;
        }
    }
}
void flatting() {
    flag = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] != group[is_visit[i][j]])
                flag = false;
            map[i][j] = group[is_visit[i][j]];
        }
    }
}
void solve() {
    int times = 0;
    while (!flag) {
        map_init();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (!is_visit[i][j]) {
                    bfs(i, j, ++group_num);
                }
            }
        }
        flatting();
        times++;
    }
    cout << times-1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}