#include <cmath>
#include <iostream>
using namespace std;

double a;
void init() { cin >> a; }

void solve() {
    cout << fixed;
    cout.precision(8);
    cout << sqrt(a) * 4;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}