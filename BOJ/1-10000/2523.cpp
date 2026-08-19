#include <iostream>

using namespace std;
int N;
void init() { cin >> N; }

void solve() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i; j++)
            cout << "*";
        cout << "\n";
    }
    for (int i = N - 1; i >= 1; i--) {
        for (int j = 1; j <= i; j++)
            cout << "*";
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}