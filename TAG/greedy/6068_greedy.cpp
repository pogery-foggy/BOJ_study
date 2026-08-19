#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N, ti, si;
long long answer;
vector<pair<int, int>> TS;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second) {
        return a.first > b.first;
    }
    return a.second > b.second;
}

void init() {
    cin >> N;
    TS.resize(N);
    for (auto &a : TS) {
        cin >> ti >> si;
        a = make_pair(ti, si);
    }
    sort(TS.begin(), TS.end(), cmp);
}

void solve() {
    answer = TS[0].second;
    for (int i = 0; i < TS.size(); i++) {
        if (answer > TS[i].second) {
            answer = TS[i].second;
        }
        answer -= TS[i].first;
    }
    if (answer < 0)
        cout << -1;
    else
        cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}