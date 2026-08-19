#include <iostream>

using namespace std;
int N, L, D, time, sec = 1;
char type;
void init() {
    cin >> N >> L >> D;
    time = 0;
    type = 'Y';
}
// 9 14 23 28 37 42
// N 곡수, L 길이, D 전화벨
void solve() {
    while (time < N * (L + 5)) {
        if (type == 'Y') {
            if (sec == L) {
                type = 'N';
                sec = 0;
            }
            ++sec;
        } else {
            if (!(time % D))
                break;
            if (sec == 5) {
                type = 'Y';
                sec = 0;
            }
            ++sec;
        }
        ++time;
    }

    while (time % D)
        ++time;
    cout << time;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}