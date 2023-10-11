#include <iostream>

using namespace std;
int N, a, b, maxi;
void init() {}

void solve() {
    while (1) {
        cin >> a >> b;
        N += b - a;
        maxi = maxi > N ? maxi : N;
        if (b == 0)
            break;
    }
    cout << maxi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}