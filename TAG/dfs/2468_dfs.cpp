#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N;
int map[101][101];
bool is_visit[101][101];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int maxi = 0;

bool is_valid(int y, int x) {
    if (x < 0 || x >= N)
        return false;
    if (y < 0 || y >= N)
        return false;
    return true;
}

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            maxi = max(maxi, map[i][j]);
        }
    }
}

void init_visit() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            is_visit[i][j] = false;
        }
    }
}

void dfs(int y, int x, int rain) {
    is_visit[y][x] = true;
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (!is_valid(ny, nx))
            continue;
        if ((!is_visit[ny][nx]) && map[ny][nx] > rain) {
            dfs(ny, nx, rain);
        }
    }
}

void solve() {
    int answer = 0;
    for (int rain = 0; rain < maxi; rain++) {
        int cnt = 0;
        init_visit();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if ((!is_visit[i][j]) && map[i][j] > rain) {
                    dfs(i, j, rain);
                    cnt++;
                }
            }
        }
        answer = max(answer, cnt);
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}