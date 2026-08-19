#include <iostream>
#include <string>
#include <vector>
using namespace std;

string s1, s2;
vector<int> cur;

void init() {
    cin >> s1 >> s2;
    cur.resize(s1.size() + s2.size());
    for (int i = 0; i < 8; i++) {
        cur[2 * i] = s1[i] - '0';
        cur[2 * i + 1] = s2[i] - '0';
    }
}

void solve() {
    vector<int> temp;
    while (1) {
        temp.resize(cur.size() - 1);
        for (int i = 0; i < temp.size(); i++) {
            temp[i] = (cur[i] + cur[i + 1]) % 10;
        }
        cur.resize(temp.size());
        cur = temp;
        if (cur.size() == 2)
            break;
    }
    cout << temp[0] << temp[1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}