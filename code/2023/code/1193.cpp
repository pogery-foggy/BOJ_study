#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int userIn, remain = 0, row = 0;
    cin >> userIn;
    remain = userIn;
    while (1) {
        if (userIn - row <= 0) {
            if (userIn != 0)
                remain = userIn;
            break;
        }
        userIn -= row;
        row += 1;
    }
    if (row % 2 == 1)
        cout << row - remain + 1 << "/" << remain;
    else
        cout << remain << "/" << row - remain + 1;
    return 0;
}