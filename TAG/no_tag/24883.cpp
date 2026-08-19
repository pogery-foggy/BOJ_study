#include <iostream>

using namespace std;

char check;

void init() { cin >> check; }

void solve() {
    if (check == 'n' || check == 'N')
        cout << "Naver D2";
    else
        cout << "Naver Whale";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}