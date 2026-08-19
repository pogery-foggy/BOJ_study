#include <iostream>
#include <string>
using namespace std;

int map[64][64], N;
bool visit[64][64];
string answer;

void init() {
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];
    answer = "Hing";
}

void DFS(int x, int y) {
    if (map[x][y] == -1)
        answer = "HaruHaru";
    visit[x][y] = true;
    if (x + map[x][y] < N) {
        if (!(visit[x + map[x][y]][y]))
            DFS(x + map[x][y], y);
    }
    if (y + map[x][y] < N) {
        if (!(visit[x][y + map[x][y]]))
            DFS(x, y + map[x][y]);
    }
}

void solve() {
    DFS(0, 0);
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}