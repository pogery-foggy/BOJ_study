#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> arr, cpy;
int N;

void init() {
    int user_in;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> user_in;
        arr.push_back(user_in);
        cpy.push_back(user_in);
    }
}

void solve() {
    sort(cpy.begin(), cpy.end());
    cpy.erase(unique(cpy.begin(), cpy.end()), cpy.end());
    for (auto ans : arr) {
        cout << lower_bound(cpy.begin(), cpy.end(), ans) - cpy.begin() << " ";
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