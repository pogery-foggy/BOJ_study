#include <iostream>
// 별찍기 5? 개량한거
using namespace std;

void init() {}

void solve() {
    int N;
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            cout << " ";
        }
        for (int j = N - i - 1; j < N + i; j++) {
            if (j == N - i - 1 || j == N + i - 1) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << "\n";
    }
    for (int i = 0; i < 2 * N - 1; i++) {
        cout << "*";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}