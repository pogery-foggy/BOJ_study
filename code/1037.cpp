#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> arr;

void init() {
    cin >> N;
    arr.resize(N);
    for (auto &x : arr) {
        cin >> x;
    }
}

void solve() {
    sort(arr.begin(), arr.end());
    cout << arr[0] * arr[arr.size() - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}