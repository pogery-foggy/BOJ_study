#include <iostream>
#include <string>
using namespace std;

string s;
int shift, space, l, r;
void init() { getline(cin, s); }

void solve() {
    for (auto a : s) {
        if (a >= 'A' && a <= 'Z') {
            shift++;
            a = a - 'A' + 'a';
        }
        if (a == ' ')
            space++;
        else if (a == 'q' || a == 'w' || a == 'e' || a == 'r' || a == 't' || a == 'y' || a == 'a' || a == 's' || a == 'd' || a == 'f' || a == 'g' || a == 'z' ||
                 a == 'x' || a == 'c' || a == 'v' || a == 'b')
            l++;
        else
            r++;
    }
    while (space--) {
        if (l <= r)
            l++;
        else
            r++;
    }
    while (shift--) {
        if (l <= r)
            l++;
        else
            r++;
    }
    cout << l << " " << r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}