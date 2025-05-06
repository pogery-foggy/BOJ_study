#include <algorithm>
#include <iostream>
using namespace std;

struct Block {
    // reverse left and right : true or false
    int lr;
    // reverse up and down : true or false
    int ud;
    // rotate 0 90 180 270 0 1 2 3
    int rot;
    // 0 1
    // 3 2
    int location;
};

// 4개로 분리할까
int map[100][100], N, M, R;
int height, width;
int block[4][50][50], copy_block[4][50][50];
Block B[4];
int print_order[] = {0, 1, 3, 2};

void init() {
    cin >> N >> M >> R;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }

    height = N / 2;
    width = M / 2;

    // 01
    // 32

    for (int i = 0; i < 4; i++) {
        B[i].lr = false;
        B[i].ud = false;
        B[i].rot = 0;
        B[i].location = i;
    }
}

void divide_area() {
    int order_y[] = {0, 0, height, height};
    int order_x[] = {0, width, width, 0};

    for (int b = 0; b < 4; b++) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                block[b][i][j] = map[i + order_y[b]][j + order_x[b]];
            }
        }
    }
}

void load_area() {
    // 0
    for (int b = 0; b < 4; b++) {
        if (B[b].lr) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    copy_block[b][i][j] = block[b][i][width - 1 - j];
                }
            }
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    block[b][i][j] = copy_block[b][i][j];
                }
            }
        }
        if (B[b].ud) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    copy_block[b][i][j] = block[b][height - 1 - i][j];
                }
            }
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    block[b][i][j] = copy_block[b][i][j];
                }
            }
        }

        if (B[b].rot == 1) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    copy_block[b][j][i] = block[b][height - 1 - i][j];
                }
            }
            // height랑 width스왑하기전에 임시로
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    block[b][i][j] = copy_block[b][i][j];
                }
            }
        }

        else if (B[b].rot == 2) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    copy_block[b][i][j] = block[b][height - 1 - i][width - 1 - j];
                }
            }
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    block[b][i][j] = copy_block[b][i][j];
                }
            }
        }

        else if (B[b].rot == 3) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    copy_block[b][j][i] = block[b][i][width - 1 - j];
                }
            }
            // height랑 width스왑하기전에 임시로
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    block[b][i][j] = copy_block[b][i][j];
                }
            }
        }
    }
    // []안에 무슨 숫자가 오든 상관없음
    if (B[0].rot == 1 || B[0].rot == 3) {
        int temp = width;
        width = height;
        height = temp;
    }
    /*
        for (int k = 0; k < 4; k++) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    cout << block[k][i][j];
                }
                cout << "\n";
            }
            cout << "\n";
        }*/
    // copy를 만들고*/
}

void print_block(int b, int loc) {

    int order_y[] = {0, 0, height, height};
    int order_x[] = {0, width, width, 0};
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map[i + order_y[loc]][j + order_x[loc]] = block[b][i][j];
        }
    }
}

void solve() {

    divide_area();

    for (int query = 0; query < R; query++) {
        int Q;
        cin >> Q;
        switch (Q) {
            // 반전은 90 270일때 반대로 적용시켜야 함
        case 1: // ud
            for (int i = 0; i < 4; i++) {
                if (B[i].rot == 1 || B[i].rot == 3)
                    B[i].lr ^= 1;
                else
                    B[i].ud ^= 1;

                B[i].location = 3 - B[i].location;
            }
            break;
        case 2: // lr
            for (int i = 0; i < 4; i++) {
                if (B[i].rot == 1 || B[i].rot == 3)
                    B[i].ud ^= 1;
                else
                    B[i].lr ^= 1;

                B[i].location = B[i].location ^ 1;
            }
            break;
        case 3: // 90
            for (int i = 0; i < 4; i++) {
                B[i].rot = (B[i].rot + 1) % 4;
                B[i].location = (B[i].location + 1) % 4;
            }
            break;
        case 4: // -90
            for (int i = 0; i < 4; i++) {
                B[i].rot = (B[i].rot + 3) % 4;
                B[i].location = (B[i].location + 3) % 4;
            }
            break;
        case 5: // +1
            for (int i = 0; i < 4; i++) {
                B[i].location = (B[i].location + 1) % 4;
            }
            break;
        case 6: // -1
            for (int i = 0; i < 4; i++) {
                B[i].location = (B[i].location + 3) % 4;
            }
            break;
        }
    }
    // query end
    
    load_area();
    for (int i = 0; i < 4; i++) {
        print_block(i, B[i].location);
    }

    for (int i = 0; i < height * 2; i++) {
        for (int j = 0; j < width * 2; j++) {
            cout << map[i][j] << " ";
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