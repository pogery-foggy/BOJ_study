#include <iostream>
#include <string>
using namespace std;

string s;
int a, b;
void init() { cin >> s >> a >> b; }

void solve() {
    for (int i = 0; i < s.size(); i++) {
        if (!(a <= i && i < b))
            cout << s[i];
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}