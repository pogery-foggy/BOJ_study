#include <iostream>
#include <string>
using namespace std;

int a, b, c;
char d, e;
void init() { cin >> a >> d >> b >> e >> c; }

void solve() {
    if (a + b == c)
        cout << "YES";
    else
        cout << "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}