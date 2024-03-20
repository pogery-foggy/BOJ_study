#include <iostream>
#include <string>
using namespace std;

string s;
void init() { getline(cin, s); }

void solve() {
    if (s == "Give you up")
        cout << "NO";
    else if (s == "Let you down")
        cout << "NO";
    else if (s == "Run around and desert you")
        cout << "NO";
    else if (s == "Make you cry")
        cout << "NO";
    else if (s == "Say goodbye")
        cout << "NO";
    else if (s == "Tell a lie and hurt you")
        cout << "NO";
    else
        cout << "YES";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}