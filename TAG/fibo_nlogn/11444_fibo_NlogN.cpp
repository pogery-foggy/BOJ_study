#include <iostream>
#include <map>
#define DIV 1000000007

using namespace std;

long long N;
map<long long, long long> dp;

void init() { cin >> N; }

long long solve(long long a) {
    if (a == 1)
        return 1;
    else if (a == 2)
        return 1;
    // memoization 을 해줘야 한다 어떻게 해야할까?
    if (dp.find(a) != dp.end())
        return dp[a];
    long long h = a / 2;
    dp[a] = (solve(h + 1) * solve(a - h) + solve(h) * solve(a - h - 1)) % DIV;
    return dp[a];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    cout << solve(N);
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}