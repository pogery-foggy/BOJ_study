#include <iostream>

using namespace std;
int arr[7];
int mini, total;
void init() {
    for (int i = 0; i < 7; i++) {
        cin >> arr[i];
    }
    mini = 111110;
    total = 0;
}

void solve() {
    for (auto a : arr) {
        if (!(a & 1)) {
            total += a;
            mini = mini < a ? mini : a;
        }
    }
    cout << total << " " << mini << "\n";
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