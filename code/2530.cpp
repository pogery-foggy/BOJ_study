#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int A, B, C, D;
    cin >> A >> B >> C;
    int total = A * 60 * 60 + B * 60 + C;
    cin >> D;
    total += D;
    total %= 60 * 60 * 24;
    int hour, mi, sec;
    hour = total / 3600;
    total -= hour * 3600;
    mi = total / 60;
    total -= mi * 60;
    sec = total;
    cout << hour << " " << mi << " " << sec;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}