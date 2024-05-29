#include <iostream>
#include <vector>
#define DIV 1000000000
using namespace std;

long long dp[1000001];
vector<long long> two;
int N;

void init() {
    cin >> N;
    dp[0] = 1;
    for (int i = 1; i <= N; i <<= 1)
        two.push_back(i);
}

void solve() {
    for (int i = 0; i < two.size(); i++) {
        for (int j = two[i]; j <= N; j++) {
            dp[j] = (dp[j] + dp[j - two[i]]) % DIV;
        }
    }
    cout << dp[N];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}