#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    char grade, plma;
    cin >> grade >> plma;
    if (grade == 'A') {
        if (plma == '+')
            cout << "4.3";
        else if (plma == '0')
            cout << "4.0";
        else
            cout << "3.7";
    } else if (grade == 'B') {
        if (plma == '+')
            cout << "3.3";
        else if (plma == '0')
            cout << "3.0";
        else
            cout << "2.7";
    } else if (grade == 'C') {
        if (plma == '+')
            cout << "2.3";
        else if (plma == '0')
            cout << "2.0";
        else
            cout << "1.7";
    } else if (grade == 'D') {
        if (plma == '+')
            cout << "1.3";
        else if (plma == '0')
            cout << "1.0";
        else
            cout << "0.7";
    } else
        cout << "0.0";

    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}