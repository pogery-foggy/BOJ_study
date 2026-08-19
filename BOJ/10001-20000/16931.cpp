#include <algorithm>
#include <iostream>

using namespace std;

int N, M;
int map[101][101];

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
}

void solve() {
    int cnt = 0, left = 0, front = 0;
    cnt += N * M * 2;

    for (int i = 0; i < N; i++) {
        int maxi = 0, mini = 999999999;
        left += map[i][0];
        for (int j = 1; j < M; j++) {
            left += map[i][j] > map[i][j - 1] ? map[i][j] - map[i][j - 1] : 0;
        }
    }
    for (int j = 0; j < M; j++) {
        int maxi = 0, mini = 999999999;
        front += map[0][j];
        for (int i = 1; i < N; i++) {
            front += map[i][j] > map[i - 1][j] ? map[i][j] - map[i - 1][j] : 0;
        }
    }
    cnt += left * 2 + front * 2;
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}