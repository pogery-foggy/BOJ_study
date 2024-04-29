#include <algorithm>
#include <iostream>
using namespace std;

int arr[16][2];
int dp[17]; // 일을 할수있는, 못하는
int N;

void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i][0] >> arr[i][1];
    }
}

void solve() {
    for (int i = 1; i <= N; i++) {
        int T = arr[i][0];
        int P = arr[i][1];
        int day = T+i;
        dp[i] = max(dp[i],dp[i-1]);
        if (day-1 > N)
            continue;
        dp[day] = max(dp[day],dp[i]+P);
    }
    int maxi = 0;
    for(int i = 1; i <=N+1; i++){
        maxi = maxi>dp[i]?maxi:dp[i];
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