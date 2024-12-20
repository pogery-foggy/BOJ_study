#include <iostream>
#include <string>
using namespace std;

string s;
int N, num_upper, num_lower;
bool is_alpha;
void init() {
    cin >> s;
    is_alpha = false;
    num_upper = 0;
    num_lower = 0;
}

void solve() {
    if (s.size() > 10)
        return;
    for (auto a : s) {
        if ('A' <= a && 'Z' >= a)
            num_upper++;
        else if ('a' <= a && 'z' >= a)
            num_lower++;
        if (!(a >= '0' && a <= '9'))
            is_alpha = true;
    }
    if (!is_alpha)
        return;
    if (!(num_upper <= num_lower))
        return;
    cout << s;
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