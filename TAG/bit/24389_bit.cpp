#include <iostream>

using namespace std;

int main() {
    int x, cnt = 0, cek;
    cin >> x;
    cek = (x & (-x));
    while (cek > 0) {
        cek /= 2;
        cnt++;
    }
    cout << 32 - cnt;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}
