#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int map[11][11];
int label[11][11];
int is_visit[11][11];
int dist[11][11];
bool connected[11][11];
vector<pair<int, int>> label_location[11];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int N, M, answer = 2100000000, land;

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
}

bool is_valid(int x, int y) {
    if (x < 0 || x >= M)
        return false;
    if (y < 0 || y >= N)
        return false;
    return true;
}

void labeling(int label_num, pair<int, int> s) {
    queue<pair<int, int>> q;
    q.push(s);
    is_visit[s.first][s.second] = true;
    label[s.first][s.second] = label_num;
    label_location[label_num].push_back({s.first, s.second});
    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = cur_x + dx[i];
            int ny = cur_y + dy[i];
            if (!is_valid(nx, ny)) {
                continue;
            }
            if (map[ny][nx] == 1 && !is_visit[ny][nx]) {
                q.push({ny, nx});
                is_visit[ny][nx] = true;
                label[ny][nx] = label_num;
                // 추후 다리만들기에 쓸거임
                label_location[label_num].push_back({ny, nx});
            }
        }
    }
}
void labeling1() {
    int label_num = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 1 && !is_visit[i][j]) {
                labeling(++label_num, {i, j});
            }
        }
    }
    // 땅 개수
    land = label_num;
}
// -------------------------------

void straight(int d, int y, int x, int bridge, int s, int e) {
    int nx = x + dx[d];
    int ny = y + dy[d];

    if (!is_valid(nx, ny))
        return;

    if (map[nx][ny] == 0)
        straight(d, ny, nx, bridge + 1, s, e);
    else {
        if (label[ny][nx] != e)
            return;
        if (bridge < 2)
            return;
        if (dist[s][e] > bridge) {
            dist[s][e] = bridge;
            dist[e][s] = bridge;
            connected[s][e] = true;
            connected[e][s] = true;
        }
    }
    //여기까지 일단 다 만들었음 이제 mst구현해야함
}
void find_bridge(int s, int e) {
    for (int i = 0; i < label_location[s].size(); i++) {
        int y = label_location[s][i].first;
        int x = label_location[s][i].second;
        for (int j = 0; j < 4; j++) {
            int ny = y + dy[j];
            int nx = x + dx[j];
            if (!is_valid(nx, ny))
                continue;
            if (!map[ny][nx])
                straight(j, ny, nx, 1, s, e);
        }
    }
}

void find_dist() {
    for (int i = 1; i < land; i++) {
        for (int j = i + 1; j < land; j++) {
            find_bridge(i, j);
        }
    }
}

void solve() {
    labeling1();
    find_dist();
    // find result
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}