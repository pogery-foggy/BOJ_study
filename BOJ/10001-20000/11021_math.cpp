#include <iostream>

using namespace std;

int A, B, answer;

void init() { cin >> A >> B; }

void solve() { answer = A + B; }

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        init();
        solve();
        cout << "Case #" << test_case << ": " << answer << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}