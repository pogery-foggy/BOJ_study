#include <algorithm>
#include <iostream>
using namespace std;

int arr[100001];
long long answer;
int N, L;
void init() {
    answer = 0;
    cin >> N >> L;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
}

void solve() {
    answer += arr[0];
    for (int i = 0; i < N - 1; i++) {
        int l, r;
        l = arr[i] + arr[i + 1];
        r = 2 * L - arr[i + 1] - arr[i];
        answer += min(l, r);
    }
    answer += min(arr[N - 1], L - arr[N - 1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
        cout << "Case #" << testcase + 1 << endl;
        cout << answer << endl;
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}