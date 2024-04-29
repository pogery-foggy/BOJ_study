#include <iostream>
#include <string>
using namespace std;

int alpha[26];
string user_in;

void init() { cin >> user_in; }

void solve() {
    for (auto a : user_in) {
        alpha[a - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        cout << alpha[i] << " ";
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