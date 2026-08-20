#include <iostream>
#define CLEAR 1
#define WALL 1
using namespace std;

int N, M, R, C, D;
// map
int map[51][51];
// 청소 되어있는지 판단
int is_clean[51][51];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int cleaning = 0;

void init() {
    cin >> N >> M;
    cin >> R >> C >> D;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] == WALL)
                is_clean[i][j] = CLEAR; // 벽은 청소완료처리
        }
    }
}

bool surround(int y, int x) {
    bool need_clean = false;
    for (int i = 0; i < 4; i++) {
        if (!is_clean[y + dy[i]][x + dx[i]])
            need_clean = true;
    }
    return need_clean;
}

void solve() {
    // 시작
    int y = R, x = C;
    is_clean[y][x] = CLEAR;
    cleaning++;

    while (1) {
        // 청소
        if (is_clean[y][x] != CLEAR) {
            is_clean[y][x] = CLEAR;
            cleaning++;
        }

        // 조건 탐색
        bool dirty = surround(y, x);
        // 2번 조건 후진
        if (!dirty) {
            int back = (D + 2) % 4;
            int nx = x + dx[back];
            int ny = y + dy[back];
            if (map[ny][nx] != WALL) {
                x = nx;
                y = ny;
            } else
                break;
        }

        // 3번조건
        else {
            D = (D + 3) % 4;
            int nx = x + dx[D];
            int ny = y + dy[D];
            if (is_clean[ny][nx] != CLEAR) {
                x = nx;
                y = ny;
            }
        }
    }
    cout << cleaning;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}