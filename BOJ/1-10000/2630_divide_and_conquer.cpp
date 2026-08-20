#include <iostream>

using namespace std;

int N, blue, white;
bool map[128][128];

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
}

void divide(int x, int y, int n) {
    bool b = true, w = true;
    for (int i = x; i < x + n; i++) {
        for (int j = y; j < y + n; j++) {
            if (map[i][j])
                w = false; // 파랑일때 w=false;
            if (!map[i][j])
                b = false;
        }
    }

    if (b) {
        blue++;
        return;
    }
    if (w) {
        white++;
        return;
    }
    divide(x, y, (n >> 1));
    divide(x, y + (n >> 1), (n >> 1));
    divide(x + (n >> 1), y, (n >> 1));
    divide(x + (n >> 1), y + (n >> 1), (n >> 1));
}

void solve() { divide(0, 0, N); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << white << "\n" << blue;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}