#include <algorithm>
#include <iostream>

using namespace std;
int a, b, c, maxi;
void init() { cin >> a >> b >> c; }

void solve() {
    if (a == b && b == c)
        maxi = maxi > (10000 + a * 1000) ? maxi : (10000 + a * 1000);

    else if (a != b && b != c && c != a) {
        int max_num = max({a, b, c});
        maxi = maxi > (max_num * 100) ? maxi : (max_num * 100);
    } else {
        int fnd = a ^ b ^ c;
        fnd -= a + b + c;
        fnd *= -1;
        fnd /= 2;
        maxi = maxi > (1000 + fnd * 100) ? maxi : (1000 + fnd * 100);
    }
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
    cout << maxi;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}