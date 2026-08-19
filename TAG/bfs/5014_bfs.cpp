#include <iostream>
#include <queue>
using namespace std;

int F, S, G, dy[2];
bool is_visit[1000001];

void init() {
    cin >> F >> S >> G >> dy[0] >> dy[1];
    dy[1] = dy[1] * -1;
}

bool is_valid(int y) {
    if (y <= 0 || y > F) return false;
    return true;
}
int solve() {
    queue<pair<int, int>> q;
    q.push({ S,0 });
    is_visit[S] = true;
    while (!q.empty()) {
        int cur = q.front().first;
        int btn = q.front().second;
        if (cur == G) return btn;
        q.pop();
        for (int i = 0; i < 2; i++) {
            int ny = cur + dy[i];
            if (!is_valid(ny))
                continue;
            if (!is_visit[ny]) {
                q.push({ ny,btn + 1 });
                is_visit[ny] = true;
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    int answer = solve();
    if (answer == -1)
        cout << "use the stairs";
    else cout << answer;

    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}