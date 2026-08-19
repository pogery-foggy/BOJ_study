#include <iostream>
#include <string>
using namespace std;

string dp[10001];
int N, M;
// n r = n-1 r + n-1 r-1
void init() {
    cin >> N;
    dp[0] = '0';
    dp[1] = '1';
}

string sum(string num1, string num2) {
    string ret = "";
    int size = max(num1.size(), num2.size());
    int total = 0;

    for (int i = 0; i < size || total; i++) {
        if (num1.size() > i)
            total += num1[i] - '0';
        if (num2.size() > i)
            total += num2[i] - '0';
        ret += total % 10 + '0';
        total /= 10;
    }
    return ret;
}

void solve() {

    for (int i = 2; i <= N; i++) {
        dp[i] = sum(dp[i - 1], dp[i - 2]);
    }

    for (int i = dp[N].size()-1; i >= 0; i --)
        cout << dp[N][i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();

    return 0;
}