#include <iostream>

using namespace std;

int S, T, D;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> S >> T >> D;
    cout << D / S / 2 * T << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}