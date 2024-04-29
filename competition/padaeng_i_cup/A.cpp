#include <iostream>
#include <string>
using namespace std;

int T, N, F[100];
string ph = "Padaeng_i Happy", pc = "Padaeng_i Cry";
void init() {
    cin >> T >> N;
    for (int i = 0; i < N; i++) {
        cin >> F[i];
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        T -= F[i];
    }
    if (T <= 0) {
        cout << ph;
    } else
        cout << pc;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}