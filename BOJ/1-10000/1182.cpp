#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> arr;
int N, S, total = 0, cnt = 0;

void init() {
    cin >> N >> S;
    int user_in;
    for (int i = 0; i < N; i++) {
        cin >> user_in;
        arr.push_back(user_in);
    }
    sort(arr.begin(), arr.end());
}

void dfs(int idx) {
    if (idx == N)
        return;
    for (int i = idx; i < N; i++) {
        total += arr[i];
        if (total == S) {
            cnt++;
        }
        dfs(i + 1);
        total -= arr[i];
    }
}

void solve() { dfs(0); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << cnt << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}