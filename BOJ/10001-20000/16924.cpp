#include <iostream>
#include <vector>
using namespace std;
int N, M;
vector<pair<pair<int, int>, int>> wkrk; // x,y,s;
char map[101][101];
bool is_visit[101][101];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
}

bool is_valid(int y, int x) {
    if (y < 0 || y >= N)
        return false;
    if (x < 0 || x >= M)
        return false;
    return true;
}
void solve() {
    for (int y = 1; y < N - 1; y++) {
        for (int x = 1; x < M - 1; x++) {
            bool flag = true;
            if (map[y][x] == '*') {
                int d = 1;
                while (flag) {
                    if (is_valid(y + d, x) && is_valid(y - d, x) && is_valid(y, x + d) && is_valid(y, x - d)) {
                        if (map[y + d][x] == '*' && map[y - d][x] == '*' && map[y][x + d] == '*' && map[y][x - d] == '*') {
                            wkrk.push_back({{y + 1, x + 1}, d});
                            is_visit[y][x] = true;
                            for (int i = 0; i < 4; i++) {
                                is_visit[y + dy[i] * d][x + dx[i] * d] = true;
                            }
                        } else
                            flag = false;
                        d++;
                    } else
                        flag = false;
                }
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == '*' && !is_visit[i][j]) {
                cout << -1;
                return;
            }
        }
    }
    cout << wkrk.size() << "\n";
    for (auto a : wkrk) {
        cout << a.first.first << " " << a.first.second << " " << a.second << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}