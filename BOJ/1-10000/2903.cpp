#include <iostream>

using namespace std;
int N, answer;
void init() {
    cin >> N;
    answer = 2;
}

void solve() {
    for (int i = 0; i < N; i++) {
        answer += answer - 1;
    }
    cout << answer * answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}