#include <iostream>
#define DIV 50
using namespace std;
int range, runner, cose;
void init() {
    range = 1;
    cin >> runner;
}

int solve() {
    int n = 0;
    while (1) {
        for (cose = 1; cose <= range; cose++) {
            n += 5;
            if (runner <= n)
                return cose;
        }
        for (cose = range; cose > 0; cose--) {
            n += 5;
            if (runner < n)
                return cose;
            if (runner == n && cose == 1)
                return 0;
        }
        range = (range + 1) % 5;
        if (range == 0)
            range++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    cout << solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}