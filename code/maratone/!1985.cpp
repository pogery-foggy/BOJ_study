#include <iostream>
#include <string>
using namespace std;

bool a[10], b[10];
int cnt;
string x, y;

void init() {
    for (int i = 0; i < 10; i++) {
        a[i] = b[i] = false;
    }
    cin >> x >> y;
    for (auto ch : x) {
        a[ch - '0'] = true;
    }
    for (auto ch : y) {
        b[ch - '0'] = true;
    }
    cnt = 0;
}

void solve() {
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    T = 3;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}