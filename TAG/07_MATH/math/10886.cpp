#include <iostream>

using namespace std;

int n, cnt;
void init() { cin >> n; }

void solve() {
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        if (k)
            cnt++;
    }

    if (cnt > n / 2)
        cout << "Junhee is cute!\n";
    else
        cout << "Junhee is not cute!\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}