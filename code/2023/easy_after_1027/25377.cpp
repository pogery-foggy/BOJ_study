#include <iostream>

using namespace std;
int a, b, dis = 2140000000;
void init() { cin >> a >> b; }

void solve() {
    if (b < dis && a <= b)
        dis = b;
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
    if (dis = 2140000000)
        cout << -1;
    else
        cout << dis;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}