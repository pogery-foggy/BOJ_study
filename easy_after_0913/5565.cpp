#include <iostream>

using namespace std;
int sum, a;
void init() {
    cin >> sum;
    for (int i = 0; i < 9; i++) {
        cin >> a;
        sum -= a;
    }
}

void solve() {
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}