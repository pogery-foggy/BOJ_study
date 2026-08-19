#include <iostream>

using namespace std;

void init() {}

void solve() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            cout << " ";
        }
        for (int j = 0; j < 2*i+1; j++) {
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