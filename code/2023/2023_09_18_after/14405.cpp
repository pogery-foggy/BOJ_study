#include <iostream>
#include <string>

using namespace std;

string s;
int i;
void init() { cin >> s; }

string solve() {

    while (i < s.size()) {
        if (s[i] == 'p') {
            if ((i + 1) >= s.size())
                return "NO";
            else if (s[i + 1] == 'i') {
                i += 2;
                continue;
            } else
                return "NO";
        } else if (s[i] == 'k') {
            if ((i + 1) >= s.size())
                return "NO";
            else if (s[i + 1] == 'a') {
                i += 2;
                continue;
            } else
                return "NO";
        } else if (s[i] == 'c') {
            if ((i + 2) >= s.size())
                return "NO";
            else if (s[i + 1] == 'h' && s[i + 2] == 'u') {
                i += 3;
                continue;
            } else
                return "NO";
        } else
            return "NO";
    }
    return "YES";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    cout << solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}