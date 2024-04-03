#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N;
vector<pair<int, int>> arr;
vector<int> v;
void init() {
    cin >> N;
    arr.resize(N);
    for (auto &a : arr) {
        cin >> a.first >> a.second;
    }
    sort(arr.begin(), arr.end());
}

void solve() {
    for (auto [_, a] : arr) {
        if (v.empty() || v.back() <= a)
            v.push_back(a);
        else
            *upper_bound(v.begin(), v.end(), a) = a;
    }
    cout << N - v.size() << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}