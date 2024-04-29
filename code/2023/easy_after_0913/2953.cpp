#include <iostream>

using namespace std;
int idx, a, maxi;
void init() {
    for (int i = 1; i <= 5; i++) {
        int sum = 0;

        for (int j = 0; j < 4; j++) {
            cin >> a;
            sum += a;
        }

        // 가장 큰 값 갱신
        if (sum > maxi) {
            maxi = sum;
            idx = i;
        }
    }

    cout << idx << " " << maxi;
}

void solve() {}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}