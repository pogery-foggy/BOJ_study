#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> tncjq1, tncjq2;
int N, M, answer;

void init() {
    cin >> N;
    tncjq1.clear();
    tncjq1.resize(N);
    for (auto &a : tncjq1) {
        cin >> a;
    }
    sort(tncjq1.begin(), tncjq1.end());

    cin >> M;
    tncjq2.clear();
    tncjq2.resize(N);
    for (auto &a : tncjq2) {
        cin >> a;
    }
}

void solve() {
    for (auto two : tncjq2) {
        answer = 0;
        int le = 0, ri = tncjq1.size() - 1;
        while (le <= ri) {
            int mid = (le + ri) / 2;
            if (tncjq1[mid] > two)
                ri = mid - 1;
            else if (tncjq1[mid] < two)
                le = mid + 1;
            else {
                answer = 1;
                break;
            }
        }
        cout << answer << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}