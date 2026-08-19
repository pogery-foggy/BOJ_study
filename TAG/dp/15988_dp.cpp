#include <iostream>
#define DIV 1000000009

using namespace std;
long long arr[1000001];
int N;
void init() {
    cin >> N;
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;
    arr[3] = 4;
}

long long dp(long long a) {
    if (a < 4)
        return arr[a];
    if (arr[a])
        return arr[a];
    return arr[a] = (dp(a - 1) + dp(a - 2) + dp(a - 3)) % DIV;
}

void solve() { cout << dp(N) << "\n"; }

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