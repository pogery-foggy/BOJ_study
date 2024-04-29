#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
vector<int> v;
int a, b;

void init() {
    cin >> a >> b;
    for (int i = 0; i < a + b; i++) {
        int x;
        cin >> x;
        v.push_back(x);
    }
    sort(v.begin(), v.end());
}

void solve() {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}