#include <iostream>

using namespace std;
int n;
void init() { cin >> n; }

void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i + 1; j++)
            cout << "*";
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (1) {
        init();
        if (n == 0)
            break;
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}