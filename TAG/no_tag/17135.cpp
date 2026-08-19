#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#define K 3
#define ENEMY 2
using namespace std;

int map[16][15], origin_map[16][15];
int is_visit[16][15];
int dx[] = {-1, 0, 1};
int dy[] = {0, -1, 0};
int N, M, D, answer = -1;
int enemy_cnt;
bool selected[15];
// 궁수가 설 수 있는 자리 M개
void init() {
    cin >> N >> M >> D;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            origin_map[i][j] = map[i][j];
            if (map[i][j])
                enemy_cnt++;
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

void bfs(pair<int, int> s) {
    // <<좌표>,사거리>
    queue<pair<pair<int, int>, int>> q;
    q.push({s, 1});
    is_visit[s.first][s.second] = true;
    while (!q.empty()) {
        int y = q.front().first.first;
        int x = q.front().first.second;
        int range = q.front().second;
        if (map[y][x] != 0) { // 겹칠수도 있기 때문에
            map[y][x] = ENEMY;
            return;
        }
        q.pop();
        for (int i = 0; i < 3; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (!is_valid(ny, nx))
                continue;
            if (!is_visit[ny][nx] && range < D) {
                q.push({{ny, nx}, range + 1});
                is_visit[ny][nx] = true;
            }
        }
    }
}

void remove_enemy(int &cnt, int &enemy) {
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == ENEMY) {
                map[i][j] = 0;
                cnt++;
                enemy--;
            } else if (map[i][j] == 1) {
                if (i == N - 1) {
                    map[i][j] = 0;
                    enemy--;
                } else {
                    map[i + 1][j] = 1;
                    map[i][j] = 0;
                }
            }
        }
    }
}

void simulate(int enemy) {
    vector<pair<int, int>> archer;
    int cnt = 0;
    for (int i = 0; i < M; i++) {
        if (selected[i]) {
            archer.push_back({N - 1, i});
        }
    }
    while (enemy > 0) {
        for (auto a : archer) {
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    is_visit[i][j] = false;
            bfs(a);
        }
        remove_enemy(cnt, enemy);
    }

    answer = max(answer, cnt);
}

void select(int cnt, int index) {
    if (cnt == K) {
        for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    map[i][j] = origin_map[i][j];
        simulate(enemy_cnt);
    }
    for (int i = index; i < M; i++) {
        selected[i] = true;
        select(cnt + 1, i + 1);
        selected[i] = false;
    }
}

void solve() {
    select(0, 0);
    cout << answer;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}