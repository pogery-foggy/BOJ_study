#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
queue<pair<pair<int, int>, int>> q;
int map[100][100];
bool visited[100][100];
int N, M;
void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char a;
            cin >> a;
            map[i][j] = a - '0';
        }
    }
}

int bfs() {
    visited[0][0] = true;
    q.push({{0, 0}, 1});
    while (!q.empty()) {
        pair<pair<int, int>, int> cur = q.front();
        cout << cur.first.first << ":" << cur.first.second << "\n";
        q.pop();
        if (cur.first.first == N - 1 && cur.first.second == M - 1)
            return cur.second;
        for (int i = 0; i < 4; i++) {
            int x = cur.first.first + dx[i];
            int y = cur.first.second + dy[i];
            if (x >= 0 && x < N && y >= 0 && y < M && map[x][y]) {
                if (visited[x][y])
                    continue;
                visited[x][y] = true;
                q.push({{x, y}, cur.second + 1});
            }
        }
    }
    return -1;
}

void solve() {
    int answer = bfs();
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}