#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int N;
long long arr[1000001];
long long sum;
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> arr[i];
    sum = 0;
}

void solve() {
    long long maxi = arr[N];
    for (int i = N - 1; i > 0; i--) {
        if (maxi < arr[i])
            maxi = arr[i];
        else
            sum += maxi - arr[i];
    }
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