#include <iostream>
#include <string>

using namespace std;

int cnt;
char ago;
string S;
int arr[26];

void init() {
    for (int i = 0; i < 26; i++) {
        arr[i] = 0;
    }
    cin >> S;
    ago = S[0];
}

void solve() {
    for (char a : S) {
        if (ago != a && arr[a - 'a'] != 0) {
            return;
        }
        arr[a - 'a']++;
        ago = a;
    }
    cnt++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    cout << cnt;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}