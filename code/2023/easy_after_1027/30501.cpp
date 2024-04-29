#include <iostream>
#include <string>
using namespace std;

string s;
void init() { cin >> s; }

void solve() {
    for (auto a : s) {
        if (a == 'S')
            cout << s;
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