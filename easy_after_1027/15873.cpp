#include <iostream>
#include <string>
#include <vector>
using namespace std;
string s;

void init() { cin >> s; }

pair<int, int> cond() {
    pair<int, int> temp;
    if (s.size() == 4) {
        temp.first = 10;
        temp.second = 10;
        return temp;
    }
    if (s.size() == 3) {
        temp.first = (s[0] - '0') * 10 + s[1] - '0';
        if (temp.first == 10) {
            temp.second = s[2] - '0';
            return temp;
        }
        temp.first = s[0] - '0';
        temp.second = 10;
        return temp;
    }
    if (s.size() == 2) {
        temp.first = s[0] - '0';
        temp.second = s[1] - '0';
        return temp;
    }
}

void solve() {
    pair<int, int> answer;
    answer = cond();
    cout << answer.first + answer.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}