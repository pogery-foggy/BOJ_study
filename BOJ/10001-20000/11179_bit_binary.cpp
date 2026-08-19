#include <iostream>

using namespace std;
int N, answer = 0;
void init() { cin >> N; }
// 1101
// 13(1) 6(0) 3(1) 1(1)
void solve() {
    while (N > 0) {
        answer <<= 1;
        if (N % 2 == 1)
            answer |= 1;
        N /= 2;
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}