#include <iostream>

using namespace std;

void init() {}

void solve() {
    int A, B;
    cin >> A >> B;
    if (A + B * 7 > 30)
        cout << 0;
    else
        cout << 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}