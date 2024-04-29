#include <iostream>

using namespace std;
int N, M;
void init() { cin >> N >> M; }

void solve() {
    if (M == 1 || M == 2)
        cout << "NEWBIE!";
    else if (M <= N)
        cout << "OLDBIE!";
    else
        cout << "TLE!";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}