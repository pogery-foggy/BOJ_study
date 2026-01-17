#include <cstring>
#include <iostream>
#include <queue>
#define R 0 // Right
#define C 1 // Cross
#define D 2 // Down
#define MAX_N 18
using namespace std;
typedef pair<int, pair<int, int>> piii;

int dx[] = {1, 1, 0}; // 가로, 대각선, 세로
int dy[] = {0, 1, 1};
int map[MAX_N][MAX_N];
int N;
void init() {
    cin >> N;
    // 초기화
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
        }
    }
}

bool is_valid(int y, int x) {
    if (y < 1 || N < y)
        return false;
    if (x < 1 || N < x)
        return false;
    return true;
}

bool is_blocked(int y, int x, int d) {
    switch (d) {
    case R:
        return map[y][x];
        break;
    case C:
        return map[y][x] || map[y - 1][x] || map[y][x - 1];
        break;
    case D:
        return map[y][x];
    }
    return false; // 그럴리 없지만
}

int solve() {
    // 100만보다 작다고 했기 때문에 100만번의 큐를 돌려도 상관없긴함
    // 100만번의 큐를 돌리자
    // 갈 수 있는지(맵 바깥이 아닌지),
    // 막혀있지 않은지 두가지만 체크하면 됨
    int cnt[MAX_N][MAX_N];
    memset(cnt, 0, sizeof(cnt));
    queue<piii> q;
    q.push({R, {1, 2}});
    cnt[1][2] = 1;
    while (!q.empty()) {
        int d = q.front().first;
        int y = q.front().second.first;
        int x = q.front().second.second;
        q.pop();
        switch (d) {
        case R:
            for (int i = 0; i < 2; i++) {
                int ny = y + dy[i];
                int nx = x + dx[i];
                if (!is_valid(ny, nx))
                    continue; // 유효한지
                if (is_blocked(ny, nx, i))
                    continue; // 막혀있는지
                cnt[ny][nx]++;
                q.push({i, {ny, nx}});
            }
            break;
        case C:
            for (int i = 0; i < 3; i++) {
                int ny = y + dy[i];
                int nx = x + dx[i];
                if (!is_valid(ny, nx))
                    continue; // 유효한지
                if (is_blocked(ny, nx, i))
                    continue; // 막혀있는지
                cnt[ny][nx] ++;
                q.push({i, {ny, nx}});
            }
            break;
        case D:
            for (int i = 1; i < 3; i++) {
                int ny = y + dy[i];
                int nx = x + dx[i];
                if (!is_valid(ny, nx))
                    continue; // 유효한지
                if (is_blocked(ny, nx, i))
                    continue; // 막혀있는지
                cnt[ny][nx] ++;
                q.push({i, {ny, nx}});
            }
        }
    }
    return cnt[N][N];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        cout << "#" << testcase + 1 << " " << solve() << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}