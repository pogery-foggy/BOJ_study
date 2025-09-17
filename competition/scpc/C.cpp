#include <iostream>
#include <string>
#define DIV 1000000007
using namespace std;
long long answer;
long long dp[100001][3];
int sz;
string N;
void init() {
    cin >> N;
    sz = N.size();
    dp[1][0] = 0; 
    dp[1][1] = 1;
    dp[1][2] = 1;
}

void solve() {
    int extra = 0;
    for(int i = 2; i < sz; i++){
        dp[i][1] = (dp[i-1][0] + dp[i-1][1] + dp[i-1][2])%DIV;
        dp[i][2] = (dp[i-1][0] + dp[i-1][1] + dp[i-1][2])%DIV;
        answer += (dp[i][1] + dp[i][2]) % DIV;
    }
    // 108 1-> 0 -> 0,1,2 
    // 108 101 201 204 230

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
        cout << "Case #" << testcase+1 << endl;
		cout << answer << endl;
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}