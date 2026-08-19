#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> answer;
int N, cnt;
int map[25][25];
bool visited[25][25];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char a;
            cin >> a;
            map[i][j] = a - '0';
        }
    }
}

void dfs(int x, int y) {
    cnt++;
    visited[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int nx = dx[i] + x;
        int ny = dy[i] + y;
        if (nx >= 0 && nx < N && ny >= 0 && ny < N && map[nx][ny] && !visited[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] && !visited[i][j]) {
                cnt = 0;
                dfs(i, j);
                answer.push_back(cnt);
            }
        }
    }
    sort(answer.begin(), answer.end());
    cout << answer.size() << "\n";
    for (auto a : answer) {
        cout << a << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}