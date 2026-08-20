#include <iostream>
#include <queue>
#include <vector>

using namespace std;

char map[101][101];
bool visited[101][101];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int N, can_see_red, cant_see_red;

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
}

bool valid(int x, int y) {
    if (x < 0 || x >= N)
        return false;
    if (y < 0 || y >= N)
        return false;
    return true;
}

void bfs(int x, int y, char a) {
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        x = cur.first;
        y = cur.second;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (valid(nx, ny) && !visited[nx][ny] && map[nx][ny] == a) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j]) {
                can_see_red++;
                bfs(i, j, map[i][j]);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = false;
            if (map[i][j] == 'G')
                map[i][j] = 'R';
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j]) {
                cant_see_red++;
                bfs(i, j, map[i][j]);
            }
        }
    }
    cout << can_see_red << " " << cant_see_red;
}

// 정적예측
// 일반적으론 동적예측 for문이 계속 실행될거라고 예측한다.
// taken nottaken으로 정적예측이 고정되어있더라면, 이게 마지막 for문일거라고
// prediction에 실패하면 성능 하락
// true가 더 많이 일어나면 continue가 일어날거라고 예측하면
//
// false가 더 많이 일어나면
// 성능이 같지 않을까.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}