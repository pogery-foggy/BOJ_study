#include <iostream>

using namespace std;

int N, temp, total, answer;

void init() { cin >> N; }

void solve() {
    for (int i = 1; i <= N; i++) {
        total = i;
        temp = i;
        while (temp > 0) {
            total += temp % 10;
            temp /= 10;
        }
        if (total == N) {
            answer = i;
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << answer;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}