#include <iostream>

using namespace std;

int sqrta, sqrtb, sqrtc;
int a, b, c;

bool check_pita() {
    if (sqrta == sqrtb + sqrtc)
        return true;
    if (sqrta + sqrtb == sqrtc)
        return true;
    if (sqrtb == sqrta + sqrtc)
        return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> a >> b >> c;
    while ((a | b) | c) {
        sqrta = a * a;
        sqrtb = b * b;
        sqrtc = c * c;
        if (check_pita())
            cout << "right" << '\n';
        else
            cout << "wrong" << '\n';
        cin >> a >> b >> c;
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}