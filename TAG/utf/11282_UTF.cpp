#include <iostream>
#include <string>
using namespace std;

string s;
int n;
void init() { cin >> n; }

void solve() {
    n += 3071;
    s.push_back(n / 4096 + 234);
    s.push_back(n / 64 % 64 + 128);
    s.push_back(n % 64 + 128);
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}