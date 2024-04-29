#include <iostream>
#include <regex>
#include <string>

using namespace std;

string S;

void init() { cin >> S; }

void solve() {
    //^thing 문자열의 시작
    //[thing] 안의 어떤문자도 가능
    // thing?앞의요소가 0번또는 1번 나타남
    // thing+ 1번이상 반복됨
    // thing$종료
    regex re("(^[A-F]?A+F+C+[A-F]?$)");

    if (regex_match(S, re))
        cout << "Infected!"
             << "\n";
    else
        cout << "Good"
             << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}