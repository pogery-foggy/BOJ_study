#include <iostream>

using namespace std;
int N, total;

void init() {}

void solve() {
    while (1) {
        cin >> N;
        if (N == -1)
            break;
        total += N;
    }
    cout << total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}