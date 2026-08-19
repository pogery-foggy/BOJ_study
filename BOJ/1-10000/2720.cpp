#include <iostream>

using namespace std;

int change[4] = {25, 10, 5, 1};
int C;
void init() { cin >> C; }

void solve() {
    for (int i = 0; i < 4; ++i) {
        cout << C / change[i] << " ";
        C %= change[i];
    }
    cout << "\n";
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