#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#define MAX_N 1000
using namespace std;

int dp[MAX_N + 1][MAX_N + 1];
char dir[MAX_N + 1][MAX_N + 1];
string s1, s2;
queue<char> answer;
void init() { cin >> s1 >> s2; }

void solve() {
    for (int i = 1; i <= s1.size(); i++) {
        for (int j = 1; j <= s2.size(); j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                dir[i][j] = 'D';
            } else {
                if (dp[i - 1][j] > dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                    dir[i][j] = 'I';
                } else {
                    dp[i][j] = dp[i][j - 1];
                    dir[i][j] = 'J';
                }
            }
        }
    }
    cout << dp[s1.size()][s2.size()] << "\n";
    int i = s1.size(), j = s2.size();
    string s = "";
    while (i > 0 && j > 0) {
        if (dir[i][j] == 'D') {
            s += s1[i - 1];
            i--;
            j--;
        } else if (dir[i][j] == 'I')
            i--;
        else
            j--;
    }
    for (int k = s.size() - 1; k >= 0; k--) {
        cout << s[k];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();

    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}