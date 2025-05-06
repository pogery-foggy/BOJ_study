#include <iostream>

using namespace std;

long long a, b;

void init() { cin >> a >> b; }

void solve() {
    long long mul = a * b;
    long long counter = 1;
    long long hap = 0;
    long long sa = a % 10;
    long long sb = b % 10;
    a /= 10;
    b /= 10;
    long long sc = sa * sb;
    long long result = sc;
    if (sc > 9)
        counter *= 100;
    else
        counter *= 10;
    while (a != 0 || b != 0) {
        if (a == 0) {
            hap = b % 10;
            b /= 10;
        } else if (b == 0) {
            hap = a % 10;
            a /= 10;
        } else {
            sa = a % 10;
            sb = b % 10;
            a /= 10;
            b /= 10;
            sc = sa * sb;
            hap = sc;
        }
        result += hap * counter;
        if (hap > 9)
            counter *= 100;
        else
            counter *= 10;
    }
    if (result == mul)
        cout <<1 << "\n";
    else
        cout << 0 << "\n";
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