#include <iostream>
#include <string>
using namespace std;

string s;
int sum = 10;
char ago;
void init() {
    cin >> s;
    ago = s[0];
}

void solve() {
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == ago)
            sum += 5;
        else {
            sum += 10;
            ago = s[i];
        }
    }
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}