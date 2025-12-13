#include <iostream>
#define MAX_N 20
using namespace std;
int N, M, iy, ix, K;
int map[MAX_N][MAX_N];
// E S N W
int dx[5] = {9999, 1, -1, 0, 0};
int dy[5] = {9999, 0, 0, -1, 1};

struct Dice {
    int up, E, W, S, North, down, x, y;

    Dice(int iy, int ix) : up(0), E(0), W(0), S(0), North(0), down(0), x(ix), y(iy) {}

    bool is_valid(int x, int y) {
        if (x < 0 || M - 1 < x)
            return false;

        if (y < 0 || N - 1 < y) {
            return false;
        }
        return true;
    }

    void move(int d) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (is_valid(nx, ny)) {
            rolling(d);
            x = nx;
            y = ny;
            map[y][x] = copy_down(map[y][x]);
            print_up();
        }
    }

    void rolling(int direction) {
        int temp;
        switch (direction) {
        case 1: // E
            temp = up;
            up = W;
            W = down;
            down = E;
            E = temp;
            break;

        case 2: // W
            temp = up;
            up = E;
            E = down;
            down = W;
            W = temp;
            break;

        case 3: // N
            temp = up;
            up = S;
            S = down;
            down = North;
            North = temp;
            break;

        case 4: // S
            temp = up;
            up = North;
            North = down;
            down = S;
            S = temp;
            break;
        }
    }

    void print_up() { cout << up << "\n"; }

    int copy_down(int read_number) {
        if (read_number == 0) {
            return down;
        } else {
            down = read_number;
            return 0;
        }
    }
};

void init() {
    cin >> N >> M >> iy >> ix >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
}

void solve() {
    Dice dice = Dice(iy, ix);
    for (int i = 0; i < K; i++) {
        int query;
        cin >> query;
        dice.move(query);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}