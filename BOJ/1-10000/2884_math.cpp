#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int minuet, hour, total;
    cin >> hour >> minuet;
    total = hour * 60 + minuet;
    total -= 45;
    total = (total + 24 * 60) % (24 * 60);
    cout << total / 60 << " " << total % 60 << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}