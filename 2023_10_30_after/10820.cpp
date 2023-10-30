#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

string s;
int l, u, num, space;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (getline(cin, s)) {
        l = 0, u = 0, num = 0, space = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] >= 'a' && s[i] <= 'z')
                l++;
            else if (s[i] >= 'A' && s[i] <= 'Z')
                u++;
            else if (s[i] >= '0' && s[i] <= '9')
                num++;
            else if (s[i] == ' ')
                space++;
        }

        cout << l << " " << u << " " << num << " " << space << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}