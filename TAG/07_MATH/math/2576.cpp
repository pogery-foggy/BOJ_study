#include <iostream>

using namespace std;
int sum, n, mini = 101;
void init() {
    for (int i = 0; i < 7; i++) {
        cin >> n;
        if (n % 2 == 1) {
            sum += n;
            if (n < mini)
                mini = n;
        }
    }
}

void solve() {
    if (sum == 0)
        cout << -1;
    else
        cout << sum << "\n" << mini;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}