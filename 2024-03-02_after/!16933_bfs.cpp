#include <iostream>
#include <queue>
using namespace std;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int map[1000][1000];
int wall[1000][1000];
int N, M, K;
struct xy {
    int x, y;
};

struct for_q {
    xy pos;
    int day, k, d_o_n;
};

void init() {
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char a;
            cin >> a;
            map[j][i] = a - '0';
            wall[j][i] = -1;
        }
    }
}

bool is_valid(int x, int y) {
    if (y < 0 || y >= N)
        return false;
    if (x < 0 || x >= M)
        return false;
    return true;
}

int bfs() {
    queue<for_q> q;
    q.push({0, 0, 1, K, 1});
    wall[0][0] = K;
    while (!q.empty()) {
        xy cur = q.front().pos;
        int day = q.front().day;
        int day_or_night = q.front().d_o_n;
        int k = q.front().k;
        q.pop();
        if (cur.x == M - 1 && cur.y == N - 1)
            return day;

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (!is_valid(nx, ny)) {
                continue;
            }
            //   값이 비어있으면 방문을 안한 것, 결국 벽부시는 횟수가 있는 걸 남겨놓자
            if (map[nx][ny] == 0 && wall[nx][ny] < k) {
                wall[nx][ny] = k;
                q.push({nx, ny, day + 1, k, day_or_night ^ 1});
            }
            if (k > 0 && map[nx][ny] == 1 && wall[nx][ny] < k - 1) {
                if (day_or_night == 1) {
                    wall[nx][ny] = k - 1;
                    q.push({nx, ny, day + 1, k - 1, day_or_night ^ 1});
                } else {
                    q.push({cur.x, cur.y, day + 1, k, day_or_night ^ 1});
                }
            }
        }
    }
    return -1;
}

void solve() { cout << bfs(); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}