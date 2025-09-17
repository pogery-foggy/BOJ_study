#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> ss;
int N;

void init() {
    cin >> N;
    ss.clear();
    ss.resize(N);
    for (auto &s : ss) {
        cin >> s;
    }
}

bool comp(string s1, string s2) {
    for (int i = 0; i <= max(s1.size(), s2.size()); i++) {
        // 어느 한쪽의 끝에 도달하면 글자가 없는 쪽이 앞
        if (i == s1.size() || i == s2.size()) {
            return s1.size() < s2.size();
        }
        if (s1[i] == s2[i])
            continue;

        bool s1hy = (s1[i] == '-'), s2hy = (s2[i] == '-');
        if (s1hy == true || s2hy == true)
            return s2hy;

        char s1up = toupper(s1[i]);
        char s2up = toupper(s2[i]);
        if (s1up == s2up)
            return s1[i] < s2[i];
        else
            return s1up < s2up;
    }
}

void solve() {
    sort(ss.begin(), ss.end(), comp);

    for (auto s : ss) {
        cout << s << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}