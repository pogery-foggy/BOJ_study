#include <iostream>

using namespace std;

bool arr[101][101];

int x, y, dx, dy, cnt;

void init() { cin >> x >> y >> dx >> dy; }

void solve() {
    for (int i = x; i < dx; i++) {
        for (int j = y; j < dy; j++) {
            arr[i][j] = true;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    for (int i = 0; i < 4; i++) {
        init();
        solve();
    }

    for (int i = 1; i <= 100; i++) {
        for (int j = 1; j <= 100; j++) {
            if (arr[i][j])
                cnt++;
        }
    }
    cout << cnt;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}