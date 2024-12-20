#include <iostream>
#include <vector>
using namespace std;

int alpha = 26, N;
vector<char> arr;

void init() { cin >> N; }

void solve() {
    while (N > 0) {
        int cur = N % 26;
        if (cur == 0)
            arr.push_back('Z');
        else
            arr.push_back('A' + cur - 1);
        N /= 26;
    }
    for (int i = arr.size() - 1; i >= 0; i--) {
        cout << arr[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}
