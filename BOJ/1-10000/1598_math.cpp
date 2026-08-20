#include <iostream>

using namespace std;

int a, b;
int ax, ay, bx, by, answer;
void init() { cin >> a >> b; }

void solve() {
    ax = ((a - 1) / 4) + 1;
    ay = (a-1) % 4 + 1;
    bx = ((b - 1) / 4) + 1;
    by = (b-1) % 4 + 1;
    answer += ay > by ? ay - by : by - ay;
    answer += ax > bx ? ax - bx : bx - ax;
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}