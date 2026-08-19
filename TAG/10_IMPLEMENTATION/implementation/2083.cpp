#include <iostream>
#include <string>
using namespace std;

string name;
int l, r;
bool plag;
void init() {
    cin >> name >> l >> r;
    plag = false;
}

void solve() {
    if (l > 17 || r >= 80)
        cout << name << " Senior"
             << "\n";
    else
        cout << name << " Junior"
             << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (1) {
        init();
        if (name == "#" && l == 0 && r == 0)
            break;
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}