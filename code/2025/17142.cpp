#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
vector<pair<int, int>> virus_list;
int map[51][51], virus, wall;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int is_visit[51][51];
int N, M;
bool active_birus[10];
int answer = 2100000000;
int blank;

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 0) {
                blank++;
            } else if (map[i][j] == 2) {
                virus_list.push_back({i, j});
            }
        }
    }
}
bool is_valid(int y, int x) {
    if (0 > y || y >= N)
        return false;
    if (0 > x || x >= N)
        return false;
    return true;
}

void map_init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            is_visit[i][j] = 0;
        }
    }
}

void bfs(queue<pair<int, int>> q) {
    // int cnt = 1;
    //  is_visit[sy][sx] = cnt;
    int find_blank = 0;
    int time = 1;
    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (!is_valid(ny, nx))
                continue;
            if (is_visit[ny][nx] == 0 && map[ny][nx] != 1) {
                q.push({ny, nx});
                is_visit[ny][nx] = is_visit[y][x] + 1;
                if (map[ny][nx] == 0) {
                    find_blank++;
                    time = is_visit[ny][nx];
                }
            }
        }
    }
    if (find_blank == blank) {
        answer = min(answer, time - 1);
    }
}

void selected_point(int cnt, int cur) {
    if (cnt == M) {
        queue<pair<int, int>> q;
        map_init();
        for (int i = 0; i < virus_list.size(); i++) {
            if (active_birus[i]) {
                q.push({virus_list[i].first, virus_list[i].second});
                is_visit[virus_list[i].first][virus_list[i].second] = 1;
            }
        }
        bfs(q);
        return;
    }
    for (int i = cur; i < virus_list.size(); i++) {
        if (!active_birus[i]) {
            active_birus[i] = true;
            selected_point(cnt + 1, i + 1);
            active_birus[i] = false;
        }
    }
}
// 해당하는 배열을 활성화 시켜놓고  bfs하기

void solve() {
    // map_init이 안되면 안됨 그럼 maxi가 -1이면 -1출력할까
    selected_point(0, 0);
    if (answer == 2100000000)
        cout << -1;
    else
        cout << answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}