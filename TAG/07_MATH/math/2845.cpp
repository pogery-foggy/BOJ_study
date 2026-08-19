#include <iostream>

using namespace std;

int L, P;
int arr[5];

void init() {
    cin >> L >> P;
    for (auto &a : arr)
        cin >> a;
}

void solve() {
    for (auto a : arr) {
        cout << a - (L * P) << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}