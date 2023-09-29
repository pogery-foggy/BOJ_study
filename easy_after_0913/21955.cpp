#include <iostream>
#include <string>
using namespace std;

string s;
void init() { cin >> s; }

void solve() {
    for (int i = 0; i < s.size() / 2; i++)
        cout << s[i];
    cout << " ";
    for (int i = s.size() / 2; i < s.size(); i++)
        cout << s[i];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}