#include <iostream>

using namespace std;

int s, m, a, b;
void init() {
    cin >> s >> m;
    a = (s + m) / 2;
    b = (s - m) / 2;
}

void solve() {

    if (a * 2 != s + m || (s - m) != b * 2)
        cout << -1;
    else {
        if (a >= 0 && b >= 0)
            if (a > b)
                cout << a << " " << b;
            else
                cout << b << " " << a;
        else
            cout << -1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}