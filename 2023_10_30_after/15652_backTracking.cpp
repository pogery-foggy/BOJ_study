#include <iostream>
#include <vector>
using namespace std;

int N, M, user_in;
vector<int> answer;
void init() { cin >> N >> M; }

void dfs(int cur, int cnt) {
    if (cnt == M) {
        for (auto ans : answer) {
            cout << ans << " ";
        }
        cout << "\n";
        return;
    }
    for (int i = cur; i <= N; i++) {
        answer.push_back(i);
        dfs(i, cnt + 1);
        answer.pop_back();
    }
}

void solve() { dfs(1, 0); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}