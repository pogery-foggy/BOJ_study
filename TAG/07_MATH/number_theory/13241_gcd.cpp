#include <iostream>

using namespace std;

long long a, b;
long long gcd(int x, int y) {
    if (!(x % y))
        return y;
    else {
        return gcd(y, x % y);
    }
}
void init() {
    cin >> a >> b;
    if (a < b) {
        long long temp = a;
        a = b;
        b = temp;
    }
}

void solve() {
    long long ab = a * b;
    long long tmp = gcd(a, b);
    cout << ab / tmp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}