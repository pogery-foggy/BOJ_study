#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int map[51][51];
int is_visit[51][51];
pair<int, int> cur_position;
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};
int N, M, time = 0;
int level = 1;
int level_up = 2;
bool flag;
vector<pair<int, int>> v;
bool is_valid(int y, int x) {
    if (y < 0 || y >= N)
        return false;
    if (x < 0 || x >= N)
        return false;
    return true;
}

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 9) {
                map[i][j] = 0;
                cur_position = {i, j};
            }
        }
    }
}

void map_init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            is_visit[i][j] = 0;
        }
    }
    if (level_up == 0) {
        level++;
        level_up = level + 1;
    }
}

void bfs(int y, int x) {
    queue<pair<int, int>> q;
    q.push({y, x});
    is_visit[y][x] = 1;
    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();
        if (!v.empty())
            if (is_visit[cur_y][cur_x] >= is_visit[v[0].first][v[0].second])
                continue;

        for (int i = 0; i < 4; i++) {
            int ny = cur_y + dy[i];
            int nx = cur_x + dx[i];
            if (!is_valid(ny, nx))
                continue;
            if (!is_visit[ny][nx] && map[ny][nx] <= level + 1) {
                q.push({ny, nx});
                is_visit[ny][nx] = is_visit[cur_y][cur_x] + 1;
                if (map[ny][nx] <= level && map[ny][nx] != 0) {
                    v.push_back({ny, nx});
                }
            }
        }
    }
}
bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first != b.first)
        return a.first < b.first;
    else
        return a.second < b.second;
}
bool find_fish() {
    if (v.empty())
        return false;
    sort(v.begin(), v.end(), comp);

    int y = v[0].first;
    int x = v[0].second;
    cur_position.first = y;
    cur_position.second = x;
    map[y][x] = 0;
    level_up--;
    time += is_visit[y][x] - 1;
    return true;
}
void solve() {
    flag = true;
    while (flag) {
        map_init();
        bfs(cur_position.first, cur_position.second);
        flag = find_fish();
        v.clear();
    }

    cout << time;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}