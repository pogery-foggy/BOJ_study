#include <iostream>

using namespace std;
long long N ,answer;
void init() {
    cin >> N;
}

void solve() {
    cout << (N-1)*(N)/2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}