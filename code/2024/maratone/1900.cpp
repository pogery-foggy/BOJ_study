#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct member {
    int i, p, r;
};

int N;
vector<member> arr;
bool comp(member a, member b) { return (a.p + b.p * a.r) > (b.p + a.p * b.r); }

void init() {
    cin >> N;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        arr[i] = {i + 1, a, b};
    }
    sort(arr.begin(), arr.end(), comp);
}

void solve() {
    for (auto a : arr) {
        cout << a.i << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}