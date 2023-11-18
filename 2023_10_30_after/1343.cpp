#include <iostream>
#include <string>
using namespace std;

string s;

void init() { cin >> s; }

void solve() {
    int cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'X') {
            cnt++;
            if (cnt == 4) {
                s[i - 3] = s[i - 2] = s[i - 1] = s[i] = 'A';
                cnt = 0;
            }
        } else {
            if (!(cnt == 0 || cnt == 2)) {
                cout << -1;
                return;
            } else if (cnt == 2) {
                s[i - 2] = s[i - 1] = 'B';
                cnt = 0;
            }
        }
    }
    if (cnt == 2) {
        s[s.size() - 2] = s[s.size() - 1] = 'B';
    } else if (cnt != 0) {
        cout << -1;
        return;
    }
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}