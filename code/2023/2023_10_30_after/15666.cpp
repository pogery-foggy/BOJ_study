#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N, M, user_in;
vector<int> arr, answer;
void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> user_in;
        arr.push_back(user_in);
    }
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
}

void dfs(int cnt, int idx) {
    if (cnt == M) {
        for (auto ans : answer) {
            cout << ans << " ";
        }
        cout << "\n";
        return;
    }

    for (int i = idx; i < arr.size(); i++) {
        if (1) {
            answer.push_back(arr[i]);
            dfs(cnt + 1, i);
            answer.pop_back();
        }
    }
}

void solve() { dfs(0, 0); }

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}