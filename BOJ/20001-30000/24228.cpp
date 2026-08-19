#include <iostream>

using namespace std;

long long N, R;

void init() { cin >> N >> R; }

void solve() { cout << (N + (R * 2)) - 1; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}