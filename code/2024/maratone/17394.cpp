#include <iostream>
#include <queue>
#include <vector>
using namespace std;

bool squr[1000001];
bool is_visit[1000001];
int N, A, B;
void init() {
    squr[0] = squr[1] = 1;
    for (int i = 2; i <= 316; i++) {
        if (squr[i])
            continue;
        for (int j = i * i; j <= 1000000; j += i) {
            squr[j] = 1;
        }
    }
}

int bfs(int s) {
    is_visit[s] = true;
    queue<pair<int, int>> q;
    q.push({s, 0});
    while (!q.empty()) {
        int cur = q.front().first;
        int cnt = q.front().second;
        q.pop();
        if (!squr[cur] && A <= cur && cur <= B)
            return cnt;

        if (!is_visit[cur / 2]) {
            is_visit[cur / 2] = true;
            q.push({cur / 2, cnt + 1});
        }
        if (!is_visit[cur / 3]) {
            is_visit[cur / 3] = true;
            q.push({cur / 3, cnt + 1});
        }
        if (cur > 0) {
            if (!is_visit[cur - 1]) {
                is_visit[cur - 1] = true;
                q.push({cur - 1, cnt + 1});
            }
        }
        if (cur < 1000000) {
            if (!is_visit[cur + 1]) {
                is_visit[cur + 1] = true;
                q.push({cur + 1, cnt + 1});
            }
        }
    }
}

int solve() {
    for (int i = 1; i <= 1000000; i++) {
        is_visit[i] = false;
    }
    cin >> N >> A >> B;
    bool exist_prime = false;
    for (int i = A; i <= B; i++) {
        if (!squr[i])
            exist_prime = true;
    }
    if (!exist_prime)
        return -1;

    return bfs(N);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    init();
    for (int testcase = 0; testcase < T; testcase++) {
        cout << solve() << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}