#include <iostream>
#define DIV (7 * 24 * 60 * 60)
using namespace std;

unsigned long long N, answer, fac;

void init() {
    cin >> N;
    fac = 1;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        fac *= i;
    }
    cout << fac / DIV;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}