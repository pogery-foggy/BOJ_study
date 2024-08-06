#include <iostream>

using namespace std;
bool is_visit[10001];
int arr[10001];
int N;
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        is_visit[i] = false;
        cin >> arr[i];
    }
}

void solve() {
    int cnt = 0;
    int cur = 1;
    while (!is_visit[cur] && cur != N) {
        is_visit[cur] = true;
        cnt++;
        cur = arr[cur];
    }
    if (cur == N) {
        cout << cnt << "\n";
    } else
        cout << "0\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}