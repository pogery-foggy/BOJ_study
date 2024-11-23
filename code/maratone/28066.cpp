#include <iostream>
#include <queue>
using namespace std;

queue<int> q;
int N, K;
void init() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        q.push(i);
}

void solve() {
    while (q.size() > 1) {
        int first = q.front();
        for (int i = 0; i < K && q.size() > 0; i++)
            q.pop();
        q.push(first);
    }
    cout << q.front();
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}