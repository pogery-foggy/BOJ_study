#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define MAX_N 15
using namespace std;

int dx[] = {0, 0, 1, -1, -1, 1, -1, 1}; // 일반, 대각선위, 대각선아래
int dy[] = {1, -1, 0, 0, -1, -1, 1, 1};
int answer;
int N, M;
int map[MAX_N][MAX_N];
int is_visit[MAX_N][MAX_N];

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
    answer = 0;
}

bool is_valid(int y, int x) {
    if (y < 0 || N <= y)
        return false;
    if (x < 0 || M <= x)
        return false;
    return true;
}

void dfs(int cnt, int y, int x, int total, int K) {
    if (cnt == K) {
        answer = max(answer, total);
        return;
    }
    for (int i = 0; i < 8; i++) {
        int ny = dy[i] + y;
        int nx = dx[i] + x;
        if ((x % 2 == 1) && (i == 4 || i == 5))
            continue;
        if ((x % 2 == 0) && (i == 6 || i == 7))
            continue;
        if (!is_valid(ny, nx))
            continue;
        if (is_visit[ny][nx])
            continue;
        is_visit[ny][nx] = true;
        if (cnt == 2) { // 아래로
            if (!is_visit[y + 1][x] && is_valid(y + 1, x)) {
                answer = max(answer, total + map[ny][nx] + map[y + 1][x]);
            }
            if (!is_visit[y - 1][x] && is_valid(y - 1, x)) {
                answer = max(answer, total + map[ny][nx] + map[y - 1][x]);
            }
        }
        dfs(cnt + 1, ny, nx, total + map[ny][nx], K);
        is_visit[ny][nx] = false;
    }
}

int solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dfs(0, i, j, 0, 4);
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int testcase = 1; testcase <= T; testcase++) {
        init();
        cout << "#" << testcase << " " << solve() << "\n";
    }
    return 0;
}

/*15*15*4*4*4 = 14400
j가 짝수면 대각선 위로 갈 수 있음 홀수면 대각선 아래로 갈 수 있음
*/