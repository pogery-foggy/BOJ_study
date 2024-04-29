#include <iostream>

using namespace std;

int N;
long long answer;
void init() {
    cin >> N;
    answer = 1;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        answer *= i;
        while (answer % 10 == 0) {

            answer /= 10;
        }
        answer %= 10000000;
    }
    cout << answer % 10;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}