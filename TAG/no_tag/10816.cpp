#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> arr;
int N, M;

void init() {
    int user_in;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> user_in;
        arr.push_back(user_in);
    }
    sort(arr.begin(), arr.end());
}

void solve() {
    cin >> M;
    int fnd;
    for (int i = 0; i < M; i++) {
        cin >> fnd;
        cout << upper_bound(arr.begin(), arr.end(), fnd) - lower_bound(arr.begin(), arr.end(), fnd) << " ";
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