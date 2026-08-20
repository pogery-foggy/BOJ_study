#include <cmath>
#include <iostream>
using namespace std;

long long a, b;
long long gcd(long long x, long long y) { return y > 0 ? gcd(y, x % y) : x; }
void init() { cin >> a >> b; }

void solve() {
    int cnt = 0;
    for (long long i = sqrt(a); i * i <= b; i++) {
        if (i * i > a)
            cnt++;
    }
    if (!cnt)
        cout << 0;
    else {
        long long ret = gcd(b - a, cnt);
        cout << cnt / ret << "/" << (b - a) / ret;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}