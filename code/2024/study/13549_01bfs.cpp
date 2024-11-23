#include <deque>
#include <iostream>

using namespace std;
int N, K;
int visit[200001];
void init() { cin >> N >> K; }

int bfs(int s) {
    deque<int> dq;
    dq.push_front(s);
    visit[s] = 1;
    while (!dq.empty()) {
        int cur = dq.front();
        dq.pop_front();

        if (cur == K) {
            return visit[cur] - 1;
        }

        if (cur * 2 < K * 2 && !visit[cur * 2]) {
            dq.push_front(cur * 2);
            visit[cur * 2] = visit[cur];
        }
        if (cur - 1 >= 0 && !visit[cur - 1]) {
            dq.push_back(cur - 1);
            visit[cur - 1] = visit[cur] + 1;
        }
        if (cur + 1 <= K && !visit[cur + 1]) {
            dq.push_back(cur + 1);
            visit[cur + 1] = visit[cur] + 1;
        }
    }
    return -1;
}

void solve() { cout << bfs(N); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}