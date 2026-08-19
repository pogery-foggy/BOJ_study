#include <iostream>
#include <string>
using namespace std;
string str;
void init() {}

void solve() {
    while (getline(cin, str)) {
        if (str == "#")
            break;

        int cnt = 0;
        for (char c : str)
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
                cnt++;

        cout << cnt << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}