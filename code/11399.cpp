#include <iostream>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, greater<int>> pq;
int answer, N, temp;

void init() {
    cin >> N;
    answer = 0;
}

void solve() {
    int user_in;
    for (int i = 0; i < N; i++) {
        cin >> user_in;
        pq.push(user_in);
    }
    while (!pq.empty()) {
        answer += answer + pq.top();
        pq.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << answer << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}