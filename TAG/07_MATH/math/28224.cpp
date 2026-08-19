#include <iostream>

using namespace std;

int N, A;
long long answer;

void init() { cin >> N; }

void solve() {
    for (int i = 0; i < N; i++) {
        cin >> A;
        answer += A;
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}