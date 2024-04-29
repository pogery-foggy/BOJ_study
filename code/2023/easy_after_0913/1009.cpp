#include <iostream>

using namespace std;
int a, b;
int answer[10] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};
void init() { cin >> a >> b; }

void solve() {
    int temp = 1;
    for (int i = 0; i < b; i++) {
        temp *= a;
        temp %= 10;
    }
    cout << answer[temp] << "\n";
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