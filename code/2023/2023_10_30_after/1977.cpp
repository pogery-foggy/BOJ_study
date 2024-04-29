#include <iostream>
#include <vector>
using namespace std;

vector<int> arr;
int l, r, mini, sum;

void init() {
    int i = 1;
    while (i * i <= 10000) {
        arr.push_back(i * i);
        i++;
    }
    cin >> l >> r;
}

void solve() {
    for (auto a : arr) {
        if (a >= l && a <= r) {
            if (mini == 0)
                mini = a;
            sum += a;
        }
    }
    if (mini == 0)
        cout << -1;
    else
        cout << sum << "\n" << mini;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}