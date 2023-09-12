#include <iostream>

using namespace std;

int T, maxy = -1;
void init() {}

void solve() {
    cin >> T;
    for (int i = 0; i < T; i++) {
        int A, B;
        cin >> A >> B;
        maxy = maxy > A * B ? maxy : A * B;
    }
    cout << maxy;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}