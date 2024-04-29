#include <iostream>
#include <string>

using namespace std;

string s;
int answer;

void init() {
    cin >> s;
    answer = s.size() * 2 - 1;
}

bool is_P(int start) {
    for (int i = 0; i < (s.size() - start) / 2; i++) { // 0 + start에서 시작
        if (s[i + start] != s[s.size() - i - 1])
            return false;
    }
    return true;
}

void solve() {
    for (int i = 0; i < s.size(); i++) {
        if (is_P(i)) {
            answer = s.size() + i;
            break;
        }
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}