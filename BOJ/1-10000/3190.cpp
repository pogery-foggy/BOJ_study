#include <deque>
#include <iostream>
#include <queue>

using namespace std;
int N, K, L, times;
int map[102][102];
// left = -1, right = 1;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int cur_d;
queue<pair<int, char>> rotates;
deque<pair<int, int>> dq;
void init() {
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int a, b;
        cin >> a >> b;
        map[a][b] = 1;
    }
    cin >> L;
    for (int i = 0; i < L; i++) {
        int a;
        char b;
        cin >> a >> b;
        rotates.push({a, b});
    }
}

bool is_valid(int y, int x) {
    if (y < 1 || y > N)
        return false;
    if (x < 1 || x > N)
        return false;
    if (map[y][x] == 2)
        return false;
    return true;
}
void move() {}

void rotation() {
    pair<int, char> cur = rotates.front();
    rotates.pop();
    if (cur.second == 'L')
        cur_d = (cur_d + 3) % 4;
    else
        cur_d = (cur_d + 1) % 4;
}

void solve() {
    // 시작은 1,1
    dq.push_front({1, 1});
    map[1][1] = 2;
    while (1) {
        times++;
        int y = dq.front().first;
        int x = dq.front().second;
        int ny = y + dy[cur_d];
        int nx = x + dx[cur_d];

        if (!is_valid(ny, nx))
            break;
        if (map[ny][nx] == 0) {
            map[dq.back().first][dq.back().second] = 0;
            dq.pop_back();
        }
        map[ny][nx] = 2;
        dq.push_front({ny, nx});
        if (times == rotates.front().first)
            rotation();
        }
    cout << times;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}