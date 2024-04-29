#include <iostream>

using namespace std;
int s, a, N, sum = 0;

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> s >> a;
        sum += a % s;
    }
    cout << sum;
}

void solve() {}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}