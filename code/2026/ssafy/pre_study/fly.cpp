#include <algorithm>
#include <iostream>
#define MAX_N 15
using namespace std;

int N, M;
int map[MAX_N][MAX_N];
int dx_c[] = {0, 0, 1, -1}; // cross
int dy_c[] = {1, -1, 0, 0};
int dx_d[] = {-1, 1, 1, -1}; // diagnoal cross
int dy_d[] = {-1, -1, 1, 1};
int answer;
void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
    answer = 0;
}

bool is_valid(int y, int x) {
    if (x < 0 || N <= x)
        return false;
    if (y < 0 || N <= y)
        return false;
    return true;
}

int fnd(int y, int x) {
    int cross = 0;
    for (int i = 0; i < 4; i++) {
        int ny = y;
        int nx = x;
        for (int j = 1; j < M; j++) {
            ny += dy_c[i];
            nx += dx_c[i];
            if (!is_valid(ny, nx))
                break;
            cross += map[ny][nx];
        }
    }

    int diag_cross = 0;
    for (int i = 0; i < 4; i++) {
        int ny = y;
        int nx = x;
        for (int j = 1; j < M; j++) {
            ny += dy_d[i];
            nx += dx_d[i];
            if (!is_valid(ny, nx))
                break;
            diag_cross += map[ny][nx];
        }
    }
    return max(cross, diag_cross);
}

int solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            answer = max(answer, map[i][j] + fnd(i, j));
        }
    }
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 1; testcase <= T; testcase++) {
        init();
        cout << "#" << testcase << " " << solve() << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}