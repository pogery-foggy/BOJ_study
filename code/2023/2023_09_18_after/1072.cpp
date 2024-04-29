#include <iostream>

using namespace std;
long long X, Y, Z;

void init() { cin >> X >> Y; }

void solve() {
    Z = Y * 100 / X;
    if (Z >= 99) {
        cout << -1;
    } else {
        Z++;
        long long answer = (Z * X - (100 * Y)) / (100 - Z);
        if (((Z * X - (100 * Y)) % (100 - Z)) == 0) {
            cout << answer;
        } else
            cout << answer + 1;
    }
}

// y/x * 100 = Z
//(y+n)/(x+n) * 100 = (Z+1)
// 100(Y+N) = (Z+1)(X+N)
// 99N-ZN = (Z+1)X - 100Y
//  N = ((Z+1)X- 100Y))/(100-(Z+1))

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}