#include <iostream>
#include <string>
using namespace std;
int a;
void init() { cin >> a; }

string solve() {
    if (a % 2)
        return to_string(a) + " is odd\n";
    else
        return to_string(a) + " is even\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        cout << solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}