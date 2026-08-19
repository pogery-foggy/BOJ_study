#include <iostream>

using namespace std;
int N, M;
void init() { cin >> N >> M; }

// M-1 번 잘라야 한다.
// N개의 소시지를 이어 붙인다. N-1번 잘려져 있다고 생각한다
// gcd N,M의 -1 빼주면

int gcd(int x, int y) {
    if (x % y == 0)
        return y;
    return gcd(y, x % y);
}

void solve() { cout << M - gcd(N, M); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}