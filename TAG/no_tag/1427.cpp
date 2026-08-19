#include <iostream>
#include <algorithm>
using namespace std;

string s;
void init() {
    cin >> s;
}

void solve() {
    sort(s.begin(),s.end());
    for(int i = s.size()-1;  i>=0; i--)
    cout << s[i];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}