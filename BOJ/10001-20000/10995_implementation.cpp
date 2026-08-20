#include <iostream>

using namespace std;

void init() {}

void solve() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        if (i % 2 == 1)
            cout << " ";
        for (int j = 0; j < N * 2; j++) {
            if (j % 2 == 1)
                cout << " ";
            else
                cout << "*";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}