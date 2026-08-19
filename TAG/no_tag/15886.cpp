#include <iostream>
#include <string>
using namespace std;

int N, cnt;
string S;

void init() { cin >> N >> S; }

void solve() {
    for (int i = 0; i < N - 1; i++) {
        if (S[i] == 'E' && S[i + 1] == 'W') {
            cnt++;
        }
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}