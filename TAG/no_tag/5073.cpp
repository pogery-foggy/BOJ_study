#include <iostream>

using namespace std;
int a, b, c;
void init() { cin >> a >> b >> c; }

void solve() {

    if (a == b && b == c && c == a) {
        cout << "Equilateral\n";
    } else if (a >= b + c || b >= c + a || c >= a + b) {
        cout << "Invalid\n";
    } else if (a == b || b == c || c == a) {
        cout << "Isosceles\n";
    } else if (a != b && b != c && c != a) {
        cout << "Scalene\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (1) {
        init();
        if (!a && !b && !c)
            return 0;
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}