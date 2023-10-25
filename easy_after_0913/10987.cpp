#include <iostream>
#include <string>
using namespace std;

string s;
int cnt;
void init() { cin >> s; }

void solve() {
    for (auto a : s) 
        if (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u')
            cnt++;
    
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}