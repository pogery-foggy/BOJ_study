#include <iostream>

using namespace std;

int x, y, z, answer;
void init() {
    cin >> x >> y >> z;
    answer = 0;
}

void solve() {
    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= y; j++) {
            for (int k = 1; k <= z; k++) {
                if ((i % j == j % k) && (j % k == k % i))
                    answer++;
            }
        }
    }
    cout << answer << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}