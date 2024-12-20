#include <iostream>

using namespace std;
/*
1
11
12
1121
122111
112213
12221131
1123123111
12213111213113
*/
int N;
void init() { cin >> N; }

void solve() {
    if (N < 3)
        cout << 1;
    else if (N < 6)
        cout << 2;
    else
        cout << 3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}