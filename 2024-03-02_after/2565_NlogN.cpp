#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> arr;
int n;
vector<int> v;

void solve() {
    for (auto [_, a] : arr) {
        if (v.empty() || v.back() <= a)
            v.push_back(a);
        else
            *upper_bound(v.begin(), v.end(), a) = a;
    }

    cout << n - v.size();
}

void init() {
    cin >> n;
    arr.resize(n);
    for (auto &[a, b] : arr)
        cin >> a >> b;
    sort(arr.begin(), arr.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
