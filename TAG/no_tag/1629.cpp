#include <iostream>

using namespace std;
int A, B, C;
void init() { cin >> A >> B >> C; }

long long int fnd(int b) {
    if (b == 1)
        return A % C;
    long long int ret = fnd(b / 2) % C;
    if (b % 2)
        return ret % C * ret % C * A % C;
    else
        return ret % C * ret % C;
}

void solve() { cout << fnd(B); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}