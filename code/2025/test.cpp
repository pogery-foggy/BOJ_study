#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define INIT (100)
#define DROP_BLOCKS (200)
#define CHANGE_BLOCKS (300)
#define GET_RESULT (400)

#include <iostream>
#include <queue>
#include <vector>

#define MAX_W 200
#define MAX_H 200

using namespace std;

bool flag;
int w, h, cur_height[MAX_W];
int map[MAX_H][MAX_W];
int block_cnt[2], score[2], total_score[2];
int search_start, search_end;
int find_dx[] = {1, 1, 1};
int find_dy[] = {1, 0, -1};
int is_visit[MAX_H][MAX_W];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void init(int W, int H) {
    w = W;
    h = H;
    for (int i = 0; i < w; i++) {
        cur_height[i] = 0;
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            map[i][j] = 0;
        }
    }
    block_cnt[0] = block_cnt[1] = 0;
}

bool is_valid(int y, int x) {
    if (y < 0 || y >= h)
        return false;
    if (x < 0 || x >= w)
        return false;
    return true;
}

void find_line(int s, int e) {
    for (int width = s; width <= e; width++) {
        for (int height = 0; height < cur_height[width]; height++) {
            int basic = map[height][width];
            for (int j = 0; j < 3; j++) {
                for (int k = 1; k <= 5; k++) {
                    int ny = height + find_dy[j] * k;
                    int nx = width + find_dx[j] * k;
                    if (!is_valid(ny, nx))
                        break;
                    if (basic * map[ny][nx] < 0)
                        break;
                    basic += map[ny][nx];
                }
                if (basic == 5 || basic == -5) {
                    for (int k = 1; k <= 5; k++) {
                        int ny = height + find_dy[j] * k;
                        int nx = width + find_dx[j] * k;
                        map[ny][nx] *= 2;
                    }
                }
            }
        }
    }
}

// 여기서 score 증가시켜야함, 블록 개수 감소도 해야함 지저분한데 시간이 없다
bool delete_line(int s, int e, int whose_turn) {
    bool f = false;
    for (int width = s; width <= e; width++) {
        for (int height = 0; height < cur_height[width]; height++) {
            if (map[height][width] == 2) {
                if (whose_turn == 1) {
                    score[whose_turn]++;
                }
                map[height][width] = 0;
                block_cnt[whose_turn]--;
                f = true;
            } else if (map[height][width] == -2) {
                if (whose_turn == 2) {
                    score[whose_turn]++;
                }
                map[height][width] = 0;
                block_cnt[whose_turn]--;
                f = true;
            }
        }
    }
    for (int width = s; width <= e; width++) {
        for (int height = 0; height < cur_height[width]; height++) {
            if (map[width][height] == 0) {
                int nh = height;
                cur_height[width]--;
                while (nh < cur_height[width] - 1) {
                    map[width][nh] = map[width][nh + 1];
                    // cur_height[width]--;
                    if (map[width][nh] == 0) {
                        cur_height[width]--;
                        nh--;
                    }
                    nh++;
                }
            }
        }
    }
    return f;
}

int dropBlocks(int mPlayer, int mCol) {
    score[mPlayer - 1] = 0;
    block_cnt[mPlayer - 1] += 3;
    if (mPlayer == 2)
        mPlayer = -1;
    for (int i = mCol; i < mCol + 3; i++) {
        map[++cur_height[mCol]][i] = mPlayer;
    }
    search_start = mCol - 4 > 0 ? mCol - 4 : 0;
    search_end = mCol + 6 < w ? mCol + 6 : w - 1;

    flag = true;
    while (flag) {
        find_line(search_start, search_end);
        flag = delete_line(search_start, search_end, mPlayer);
    }
    if (mPlayer == -1)
        mPlayer = 2;
    // total 스코어 증가
    total_score[mPlayer - 1] += score[mPlayer - 1];
    return score[mPlayer - 1];
}

void bfs(int whose_turn, int s) {
    queue<pair<int, int>> q;
    q.push({0, s});
    is_visit[0][s] = true;
    map[0][s] = whose_turn;
    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = cur_x + dx[i];
            int ny = cur_y + dy[i];
            if (!is_valid(ny, nx)) {
                continue;
            }
            if (map[ny][nx] == whose_turn * -1 && !is_visit[ny][nx]) {
                q.push({ny, nx});
                is_visit[ny][nx] = true;
                map[ny][nx] = whose_turn;
                search_start = search_start < nx - 4 ? search_start : nx - 4;
                search_end = search_end > nx + 4 ? search_end : nx + 4;
                if (search_start < 0)
                    search_start = 0;
                if (search_end >= w)
                    search_end = w - 1;
            }
        }
    }
}

int changeBlocks(int mPlayer, int mCol) {
    search_start = search_end = mCol;
    if (mPlayer == 2)
        mPlayer = -1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            is_visit[i][j] = 0;
        }
    }
    if (map[0][mCol] == 0 || map[0][mCol] == mPlayer)
        return 0;
    bfs(mPlayer, mCol);
    flag = true;
    while (flag) {
        find_line(search_start, search_end);
        flag = delete_line(search_start, search_end, mPlayer);
    }
    if (mPlayer == -1)
        mPlayer = 2;
    // total 스코어 증가
    total_score[mPlayer - 1] += score[mPlayer - 1];
    return score[mPlayer - 1];
}

int getResult(int mBlockCnt[2]) {
    mBlockCnt[0] = block_cnt[0];
    mBlockCnt[1] = block_cnt[1];
    if (total_score[0] == total_score[1])
        return 0;
    else if (total_score[0] > total_score[1])
        return 1;
    else
        return 2;
}

static bool run() {
    int Q, W, H;

    int mPlayer, mCol;

    int ret = -1, ans;
    int mBlockCnt[2] = {};
    int r1, r2;

    scanf("%d", &Q);

    bool okay = false;
    for (int q = 0; q < Q; ++q) {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd) {
        case INIT:
            scanf("%d %d", &W, &H);
            init(W, H);
            okay = true;
            break;
        case DROP_BLOCKS:
            scanf("%d %d", &mPlayer, &mCol);
            if (okay)
                ret = dropBlocks(mPlayer, mCol);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CHANGE_BLOCKS:
            scanf("%d %d", &mPlayer, &mCol);
            if (okay)
                ret = changeBlocks(mPlayer, mCol);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case GET_RESULT:
            if (okay)
                ret = getResult(mBlockCnt);
            scanf("%d %d %d", &ans, &r1, &r2);
            if (ans != ret || mBlockCnt[0] != r1 || mBlockCnt[1] != r2)
                okay = false;
            break;
        default:
            okay = false;
            break;
        }
    }

    return okay;
}

int main() {
    setbuf(stdout, NULL);
    // freopen("sample_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d%d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}