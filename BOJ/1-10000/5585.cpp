#include <iostream>

using namespace std;

int user_in, change, cnt;
int arr[6] = {500, 100, 50, 10, 5, 1};
void init() {
    cin >> user_in;
    change = 1000 - user_in;
}

void solve() {
    for (int i = 0; i < 6; i++) {
        cnt += change / arr[i];
        change = change % arr[i];
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}