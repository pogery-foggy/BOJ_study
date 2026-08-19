#include <iostream>

using namespace std;

int a,b;
int answer;
void init() {cin >> a >>b;
answer = 320;}

void solve() {
    if(b==1) answer = 280;
    if(a<12 || a>16) answer=280;
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}