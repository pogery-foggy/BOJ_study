#include <iostream>
#include <string>
#include <vector>

using namespace std;

int answer;
string a, b;
vector<vector<int>> LCS(1001, vector<int>(1001, 0));

void init() { cin >> a >> b; }

void solve() {
    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            if (a[i - 1] == b[j - 1]) {
                LCS[i][j] = LCS[i - 1][j - 1] + 1;
            } else
                LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
        }
    }
    answer = LCS[a.size()][b.size()];
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        init();
        solve();
        cout << "#" << test_case << " " << answer << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}