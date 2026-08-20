#include <iostream>

using namespace std;
int arr[1000], dp[1000], reverse_dp[1000];
int N;
void init() {
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
}

void solve() {
    for(int i = 0; i < N; i++){
        dp[i] = 1;
        for(int j = 0; j < i ;j++){
            if(arr[i] > arr[j])
                dp[i] = max(dp[i], dp[j]+1);
        }
    }
    for(int i = N-1; i >= 0; i--){
        reverse_dp[i] = 1;
        for(int j = N-1; j >= i ;j--){
            if(arr[i] > arr[j])
                reverse_dp[i] = max(reverse_dp[i], reverse_dp[j]+1);
        }
    }
    int answer = 1;
    for(int i = 0; i < N; i++){
        answer = max(answer, dp[i]+reverse_dp[i]);
    }
    cout << answer-1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}