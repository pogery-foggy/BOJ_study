#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = n - i; j < n; j++)
            cout << " ";
        for (int j = 0; j < (2 * (n - i - 1) + 1); j++) {
            cout << "*";
        }
        cout << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}