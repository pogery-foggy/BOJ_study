#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int N;
vector<pair<int, int>> arr;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second)
        return a.first < b.first;
    return a.second < b.second;
}

void init() {
    cin >> N;
    int user_in1, user_in2;

    for (int i = 0; i < N; i++) {
        cin >> user_in1 >> user_in2;
        arr.push_back({user_in1, user_in2});
    }
    sort(arr.begin(), arr.end(), cmp);
}

void solve() {
    for (auto a : arr) {
        cout << a.first << " " << a.second << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}