#include <iostream>
#include <string>
using namespace std;

string cmd;
int s, x, N = 20;
void init() {
    cin >> cmd;
}

void solve() {
    if (cmd == "add") {
        cin >> x;
        x--;
        s = (s | (1 << x));

    } else if (cmd == "remove") {
        cin >> x;
        x--;
        s = (s & ~(1 << x));

    } else if (cmd == "check") {
        cin >> x;
        x--;
        int check = (s & (1 << x));
        cout << (check ? 1 : 0) << '\n';

    } else if (cmd == "toggle") {
        cin >> x;
        x--;
        s = (s ^ (1 << x));

    } else if (cmd == "all") {
        s = (1 << N) - 1;

    } else { // empty
        s = 0;
    }
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