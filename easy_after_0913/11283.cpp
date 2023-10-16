#include <iostream>
#include <string>
using namespace std;

string s;
int n;
void init() { cin >> s; }

void solve() {
    n = ((s[0] & 255) - 234) * 4096 + ((s[1] & 255) - 176) * 64 + (s[2] & 255) - 127;
    cout << n << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}