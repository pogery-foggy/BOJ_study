#include <iostream>

using namespace std;
int N, sum;
void init() {
    cin >> N;
    sum = 0;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        sum += i * ((i + 1 + 1) * (i + 1) / 2);
    }
    cout << sum << "\n";
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