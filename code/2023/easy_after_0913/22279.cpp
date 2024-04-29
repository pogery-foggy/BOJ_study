#include <iostream>

using namespace std;
int N;
double answer, le, ri;
void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> le >> ri;
        answer += le * ri;
    }
}

void solve() {
    cout << fixed;
    cout.precision(3);
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