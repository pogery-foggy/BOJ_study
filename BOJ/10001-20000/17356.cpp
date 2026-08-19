#include <cmath>
#include <iostream>
using namespace std;

double a, b, answer;
void init() { cin >> a >> b; }

void solve() {
    answer = (b - a) / 400;
    cout << fixed;
    cout.precision(20);
    cout << 1 / (1 + pow(10, answer));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}