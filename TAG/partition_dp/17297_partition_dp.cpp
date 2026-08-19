#include <iostream>
#include <string>
using namespace std;

long long dp[51];
int M;

void init() {
    cin >> M;
    dp[1] = 5;
    dp[2] = 13;
    for (int i = 3; i <= 50; i++) {
        dp[i] = dp[i - 1] + dp[i - 2] + 1;
    }
}

char fnd(int cur, int x) {
    char ret;

    if (cur <= 2) {
        string a = "Messi Gimossi";
        return a[x];
    }

    if (x > dp[cur - 1])
        return fnd(cur - 2, x - dp[cur - 1] - 1);
    else if (x == dp[cur - 1])
        return ' ';
    else
        return fnd(cur - 1, x);
}

void solve() {
    int s;
    for (int i = 1; i < 40; i++) {
        if (dp[i] == M) {
            s = i + 1;
            break;
        } else if (dp[i] > M) {
            s = i + 1;
            break;
        }
    }

    char answer = fnd(45, M - 1);
    if (answer == ' ')
        cout << "Messi Messi Gimossi";
    else
        cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}