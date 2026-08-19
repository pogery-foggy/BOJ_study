#include <iostream>
#include <string>
using namespace std;
int num[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
int num2[26] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 1, 2, 3, 4};
string s;
int cng[10];
void init() {
    for (int i = 1; i <= 9; i++) {
        int a;
        cin >> a;
        cng[a] = i;
    }
    cin >> s;
}

void solve() {
    char ago = '0';
    for (int i = 0; i < s.size(); i++) {
        char a = s[i];
        if (num[ago - 'a'] == num[a - 'a'])
            cout << '#';
        for (int j = 0; j < num2[a - 'a']; j++)
            cout << cng[num[a - 'a']];
        ago = a;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}