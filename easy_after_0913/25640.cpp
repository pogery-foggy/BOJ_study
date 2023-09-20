#include <iostream>
#include <string>
using namespace std;

string s, another;
int N, cnt;
void init() {
    cin >> s;
    cin >> N;
}

void solve() {
    for (int i = 0; i < N; i++) {
        cin >> another;
        if (another == s)
            cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}