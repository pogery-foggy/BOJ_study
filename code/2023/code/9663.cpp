#include <iostream>
#include <vector>
#define MAX_N 15
using namespace std;

int N, cnt = 0;
bool con_x[MAX_N], con_cross_up[2 * MAX_N + 1], con_cross_down[2 * MAX_N + 1];

void init() { cin >> N; }

void put_queen(int x, int y) {
    con_x[x] = true;
    con_cross_up[x + y] = true;
    con_cross_down[y - x + 15] = true;
}

void erase_queen(int x, int y) {

    con_x[x] = false;
    con_cross_up[x + y] = false;
    con_cross_down[y - x + 15] = false;
}

void dfs(int y) {
    if (y == N) {
        cnt++;
        return;
    }
    for (int x = 0; x < N; x++) {
        if (con_x[x])
            continue;
        if (con_cross_up[x + y])
            continue;
        if (con_cross_down[y - x + 15])
            continue;
        put_queen(x, y);
        dfs(y + 1);
        erase_queen(x, y);
    }
}

void solve() {
    dfs(0);
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}