#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int dx[] = {1, -1};
bool visited[100001];
int N, K;
void init() { cin >> N >> K; }

bool valid(int x) {
    if (x < 0 || x > 100000)
        return false;
    return true;
}

int bfs() {
    queue<pair<int, int>> q;
    q.push({N, 0});
    visited[N] = true;
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        int x = cur.first;
        if (x == K)
            return cur.second;
        vector<int> nx;
        for (int i = 0; i < 2; i++) {
            nx.push_back(x + dx[i]);
        }
        nx.push_back(x * 2);
        for (int i = 0; i < 3; i++) {
            if (valid(nx[i]) && !visited[nx[i]]) {
                visited[nx[i]] = true;
                q.push({nx[i], cur.second + 1});
            }
        }
    }
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