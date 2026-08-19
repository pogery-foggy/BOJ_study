#include <iostream>
#define MAX_N 50
using namespace std;

int answer, M, N, K;
bool map[MAX_N][MAX_N];
bool is_visit[MAX_N][MAX_N];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void init() {
    answer = 0;
    cin >> M >> N >> K;
    int x, y;
    for (int i = 0; i < K; i++) {
        cin >> x >> y;
        map[x][y] = true;
        is_visit[x][y] = false;
    }
}

bool can_move(int x, int y) {
    if ((x >= 0 && x < M) && (y >= 0 && y < N))
        return true;
    return false;
}

void dfs(int x, int y) {
    is_visit[x][y] = true;
    for (int i = 0; i < 4; i++) {
        if (can_move(x + dx[i], y + dy[i]))
            if (map[x + dx[i]][y + dy[i]] && !is_visit[x + dx[i]][y + dy[i]])
                dfs(x + dx[i], y + dy[i]);
    }
}

void solve() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] && !is_visit[i][j]) {
                dfs(i, j);
                answer++;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        init();
        solve();
        cout << answer << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}