#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
string a, b;
void init() { cin >> a >> b; }

void solve() {
    if (a == "null") {
        cout << "NullPointerException\nNullPointerException";
    } else if (a.size() != b.size() || b == "null") {
        cout << "false\nfalse";
    } else {
        // 1
        if (a == b)
            cout << "true\n";
        else
            cout << "false\n";

        // 2
        bool flag = true;
        for (int i = 0; i < a.size(); i++) {
            if (tolower(a[i]) != tolower(b[i]))
                flag = false;
        }
        if(flag) cout << "true";
        else cout << "false";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}