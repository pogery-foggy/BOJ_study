#include <iostream>

using namespace std;
int N;
bool plag;

void init() { cin >> N; }

void solve() {
    if (N % 2 == 1)
        plag = true;
    if (plag) {
        for (int i = 0; i < N - 1; i++) {
            if (i % 2 == 0)
                cout << 1<< " ";
            else
                cout << 2<< " ";
        }
        cout << 3;
    } else {
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0)
                cout << 1<< " ";
            else
                cout << 2<< " ";
        }
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