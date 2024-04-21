#include <iostream>
#include <string>
#include <vector>

using namespace std;

int answer;
string a, b;
vector<vector<int>> knap(101, vector<int>(1001, 0));
vector<pair<int, int>> N;
int K, Ncnt;
void init() {
    int V, C;
    cin >> Ncnt >> K;
    N.clear();
    for (int i = 0; i < Ncnt; i++) {
        cin >> V >> C;
        N.push_back({V, C});
    }
}

void solve() {
    for (int i = 1; i <= Ncnt; i++) {
        for (int j = 1; j <= K; j++) {
            if (N[i - 1].first <= j) {
                knap[i][j] = max(N[i - 1].second + knap[i - 1][j - N[i - 1].first], knap[i - 1][j]); //
            } else
                knap[i][j] = knap[i - 1][j];
        }
    }
    answer = knap[Ncnt][K];
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