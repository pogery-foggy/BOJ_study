#include <iostream>
#include <string>
using namespace std;
int A, B, x, y;
void init() {
    A = 0;
    B = 0;
    for (int i = 0; i < 9; i++) {
        cin >> x >> y;
        A += x;
        B += y;
    }
}

void solve() {
    if (A > B)
        cout << "Yonsei\n";
    else if (A < B)
        cout << "Korea\n";
    else
        cout << "Draw\n";
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