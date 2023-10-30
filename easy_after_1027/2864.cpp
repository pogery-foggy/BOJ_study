#include <iostream>
#include <string>
using namespace std;
string a, b, c, d;
void init() {
    cin >> a >> b;
    c = a;
    d = b;
}

void solve() {
    for (auto &x : a) {
        if (x == '5')
            x = '6';
    }
    for (auto &x : b) {
        if (x == '5')
            x = '6';
    }
    for (auto &x : c) {
        if (x == '6')
            x = '5';
    }
    for (auto &x : d) {
        if (x == '6')
            x = '5';
    }

    cout << stoi(c) + stoi(d) << " " << stoi(a) + stoi(b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}