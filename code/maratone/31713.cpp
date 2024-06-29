#include <iostream>

using namespace std;
int a, b;

// 3 3 3 4
// 3 3 4
// 3 4
void init() { cin >> a >> b; }

void solve() {
    int answer = 2147483647;
    for (int i = a; i <= 1000; i++) {
        int maxi = i * 4;
        int mini = i * 3;
        if (b < mini) {
            answer = answer < (mini - b) + (i - a) ? answer : (mini - b) + (i - a);
        } else if (mini <= b && b <= maxi)
            answer = answer < (i - a) ? answer : (i - a);
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