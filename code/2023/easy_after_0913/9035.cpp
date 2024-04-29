#include <iostream>

using namespace std;
int arr[101], N, sum;

void init() {
    sum = 0;
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i];
}

void solve() {
    for (int i = 0; i < N; i++)
        sum += arr[i];
    cout << sum << "\n";
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