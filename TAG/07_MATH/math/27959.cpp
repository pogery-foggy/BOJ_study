#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int A, B;
    cin >> A >> B;
    if (A * 100 >= B) {
        cout << "Yes";
    } else
        cout << "No";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}