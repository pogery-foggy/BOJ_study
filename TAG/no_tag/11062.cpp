#include <iostream>

using namespace std;

int N, card[1001], score[1001][1001];

void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> card[i];
        for (int j = 1; j <= N; j++) {
            score[i][j] = 0;
        }
    }
}

int play(int l, int r, bool gnu) {
    if (l > r)
        return 0;
    if (score[l][r])
        return score[l][r];
    if (gnu) {
        return score[l][r] = max(play(l + 1, r, !gnu) + card[l], play(l, r - 1, !gnu) + card[r]);
    } else {
        return score[l][r] = min(play(l + 1, r, !gnu), play(l, r - 1, !gnu));
    }
}

void solve() { cout << play(1, N, true) << "\n"; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}