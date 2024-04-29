#include <iostream>

using namespace std;
int N, cnt[5];
void init() { cin >> N; }

void solve() {
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        if (x == 0 || y == 0) {
            cnt[0]++;
        } else if (x > 0 && y > 0)
            cnt[1]++;
        else if (x < 0 && y > 0)
            cnt[2]++;
        else if (x < 0 && y < 0)
            cnt[3]++;
        else if (x > 0 && y < 0)
            cnt[4]++;
    }
    cout << "Q1: " << cnt[1]<<"\n";
    cout << "Q2: " << cnt[2]<<"\n";
    cout << "Q3: " << cnt[3]<<"\n";
    cout << "Q4: " << cnt[4]<<"\n";
    cout << "AXIS: " << cnt[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}