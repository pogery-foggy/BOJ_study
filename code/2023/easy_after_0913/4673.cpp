#include <iostream>

using namespace std;

bool check[10001];
int s, a;

void init() {}

void solve() {

    for (int i = 1; i <= 10000; i++) {
        s = 0;
        a = i;
        while (a != 0) {
            s += a % 10;
            a /= 10;
        }
        if (i + s <= 10000) {
            check[i + s] = true;
        }
    }

    for (int i = 1; i <= 10000; i++) {
        if (!check[i]) { // 생성자 없는 수 출력
            cout << i << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}