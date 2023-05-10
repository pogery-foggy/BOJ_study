#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define MAX_N 100000
using namespace std;

int N, M, idx;
string ID, password;
vector<pair<string, string>> arr;

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> ID >> password;
        arr.push_back({ID, password});
    }
    sort(arr.begin(), arr.end());
}

int b_s(int l, int r, string fnd) {
    int mid = (l + r) >> 1;
    if (arr[mid].first == fnd)
        return mid;
    return arr[mid].first > fnd ? b_s(l, mid, fnd) : b_s(mid + 1, r, fnd);
}

void solve() {
    string fnd;
    for (int i = 0; i < M; i++) {
        cin >> fnd;
        int idx = b_s(0, N - 1, fnd);
        cout << arr[idx].second << "\n";
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