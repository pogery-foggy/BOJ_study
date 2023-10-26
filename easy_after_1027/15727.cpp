#include <iostream>

using namespace std;
int N;
void init() { cin >> N; }

void solve() {
    if (N % 5 == 0)
        cout << N / 5;
    else
        cout << N / 5 + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}