#include <cmath>
#include <iostream>
#define PI 3.14159265358979323846

using namespace std;
double r, answer;
double a;
// r*r*PI = a
void init() {
    cin >> a;
    a /= PI;
    r = sqrt(a);
}

void solve() {
    answer = 2 * r * PI;

    cout << fixed;
    cout.precision(7);
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}