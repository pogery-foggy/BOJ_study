#include <iostream>

using namespace std;

long long A, B, C;
void init() { cin >> A >> B >> C; }

void solve() {
    if ((A + B) < C * 2)
        cout << A + B;
    else
        cout << (A + B) - C * 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}