#include <iostream>
#include <string>
using namespace std;
string s;
void init() {
    getline(cin, s);
}

void solve() {
    if(s[0] >= 'a' && s[0] <= 'z')
        s[0] += 'A'-'a';
    cout << s << "\n"; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    cin.ignore();
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}