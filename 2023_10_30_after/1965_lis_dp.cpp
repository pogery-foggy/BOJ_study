#include <iostream>

using namespace std;
int N, maxi, dp[1001], arr[1001];
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> arr[i];
}

void solve() {
    for (int i = 1; i <= N; i++){
        dp[i]=1;
        for(int j = 1; j <i; j++){
            if(arr[j] < arr[i] && dp[i] < dp[j] + 1){
                dp[i] = dp[j] + 1;
            }
        }
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