#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;
int N;
vector<int> v;

void init() {
    cin >> N;
    arr.resize(N);
    for (auto &a : arr)
        cin >> a;
}

void solve() {
    for (auto a : arr) {
        if (v.empty() || v.back() < a)
            v.push_back(a);
        else
            *upper_bound(v.begin(), v.end(), a - 1) = a;
    }

    cout << v.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
