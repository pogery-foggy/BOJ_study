#include <iostream>
#include <string>
#define DIV 1234567891
#define TO 31
using namespace std;

int N;
string user_in;
long long answer = 0, cnt = 1;

void init() {
    cin >> N;
    cin >> user_in;
}

void solve() {
    for (auto a : user_in) {
        answer = (answer + ((a - 'a' + 1) * cnt)) % DIV;
        cnt = (cnt * TO) % DIV;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << answer << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}