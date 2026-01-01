#include <algorithm>
#include <iostream>

using namespace std;

int N, B, arr[20], mini;
void init() {
    cin >> N >> B;
    mini = 2100000000;
    for(int i =0; i < N; i++)cin >> arr[i];
}

void solve(int cur, int height) {
    if (height >= B){
        mini = min(mini, height);
        return;
    }
    for (int i = cur; i < N; i++) {
        solve(i + 1, height + arr[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 1; testcase <= T; testcase++) {
        init();
        solve(0, 0);
        cout << "#" << testcase << " " << mini - B << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}