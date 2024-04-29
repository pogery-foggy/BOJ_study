#include <iostream>

using namespace std;

int A, B, C, result;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> A >> B >> C;
    if (A == B && B == C)
        cout << "*";
    else if (A == B)
        cout << "C";
    else if (B == C)
        cout << "A";
    else if (A == C)
        cout << "B";

    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}