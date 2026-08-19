#include <iostream>
#include <string>

using namespace std;
string A, B;

void init() { cin >> A >> B; }

void solve() {
    for (int i = 0; i < A.size(); i++) {
        int answer;
        answer = (A[i] > B[i]) ? A[i] - '0' : B[i] - '0';
        cout << answer;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}