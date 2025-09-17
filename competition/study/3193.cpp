#include <iostream>

using namespace std;
char map[1001][1001];
int arrive[1001][1001][4]; // 0U 1R 2D 3L;
int N, K, sy, sx;
void init() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 'L') {
                sy = i;
                sx = j;
            }
        }
    }
    // L
    for (int i = 0; i < N; i++) {
        int X = -1;
        for (int j = 0; j < N; j++) {
            arrive[i][j][3] = X + 1;
            if (map[i][j] == 'X')
                X = j;
        }
    }
    // R
    for (int i = 0; i < N; i++) {
        int X = N;
        for (int j = N - 1; j >= 0; j--) {
            arrive[i][j][1] = X - 1;
            if (map[i][j] == 'X')
                X = j;
        }
    }
    // U
    for (int i = 0; i < N; i++) {
        int X = -1;
        for (int j = 0; j < N; j++) {
            arrive[j][i][0] = X + 1;
            if (map[j][i] == 'X')
                X = j;
        }
    }
    // D
    for (int i = 0; i < N; i++) {
        int X = N;
        for (int j = N - 1; j >= 0; j--) {
            arrive[j][i][2] = X - 1;
            if (map[j][i] == 'X')
                X = j;
        }
    }
}

void solve() {
    // 0U 1R 2D 3L;
    int ground = 2; // 중력
    int ny = sy, nx = sx;
    for (int i = 0; i < K; i++) {
        char input;
        cin >> input;
        if (input == 'L') {
            ground = (ground + 1) % 4;
        } else {
            ground = (ground + 3) % 4;
        }
        switch (ground) {
        case 0: // U
            ny = arrive[ny][nx][0];
            break;
        case 1: // R
            nx = arrive[ny][nx][1];
            break;
        case 2: // D
            ny = arrive[ny][nx][2];
            break;
        case 3: // L
            nx = arrive[ny][nx][3];
            break;
        }
    }
    map[sy][sx] = '.';
    map[ny][nx] = 'L';

    switch (ground) {
    case 0: // U
        for (int i = N - 1; i >= 0; i--) {
            for (int j = N - 1; j >= 0; j--) {
                cout << map[i][j];
            }
            cout << "\n";
        }
        break;
    case 1: // R
        for (int i = 0; i < N; i++) {
            for (int j = N - 1; j >= 0; j--) {
                cout << map[j][i];
            }
            cout << "\n";
        }
        break;
    case 2: // D
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << map[i][j];
            }
            cout << "\n";
        }
        break;
    case 3: // L
        for (int i = N - 1; i >= 0; i--) {
            for (int j = 0; j < N; j++) {
                cout << map[j][i];
            }
            cout << "\n";
        }
        break;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}