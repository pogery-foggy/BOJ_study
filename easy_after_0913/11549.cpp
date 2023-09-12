#include <iostream>

using namespace std;

void init() {}

void solve() {
    int A, B, cnt = 0;
    cin >> A;
    for (int i = 0; i < 5; i++) {
        cin >> B;
        if (A == B)
            cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}