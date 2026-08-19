#include <iostream>

using namespace std;
int N;
int a[100], b[100];
void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> b[i];
    }
}

int abs(int x, int y) {
    if (x - y < 0)
        return -1 * (x - y);
    else
        return x - y;
}

void solve() {
    int answer = 0;
    for (int i = 0; i < N; i++) {
        answer += abs(a[i], b[i]);
    }
    cout << answer / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}