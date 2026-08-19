#include <iostream>

using namespace std;

int N, answer;

void init() { cin >> N; }

void solve() {
    if (N == 1 || N == 3)
        answer = -1;
    else if ((N%5) % 2 == 1) {
        answer += N / 5 - 1;
        N %= 5;
        N += 5;
        answer += N / 2;
    } else {
        answer += N / 5;
        N %= 5;
        answer += N / 2;
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