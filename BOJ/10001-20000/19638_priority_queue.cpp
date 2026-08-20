#include <iostream>
#include <queue>
using namespace std;

priority_queue<int> pq;
int N, T, lowe;
void init() {
    cin >> N >> lowe >> T;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        pq.push(a);
    }
}

void solve() {
    int time = T;
    int answer = -1;
    while (time--) {
        int cur = pq.top();
        pq.pop();
        if (lowe > cur) {
            answer = T - time - 1;
            break;
        }
        if (cur > 1)
            cur /= 2;
        pq.push(cur);
    }
    if (lowe > pq.top()) {
        answer = T - time - 1;
    }
    if (answer < 0) {
        cout << "NO\n" << pq.top();
    } else
        cout << "YES\n" << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}