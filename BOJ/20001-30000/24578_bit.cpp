#include <iostream>

using namespace std;
char a[4];
int arr[4];
char clck[4][4];

int main() {
    cin >> a[0] >> a[1] >> a[2] >> a[3];
    for (int i = 0; i < 4; i++) {
        arr[i] = a[i] - '0';
    }
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            if (arr[i] & (1 << k))
                clck[i][k] = '*';
            else
                clck[i][k] = '.';
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == 2)
                cout << "  ";
            cout << clck[j][4 - i - 1];
            if (j != 3)
                cout << " ";
        }
        cout << "\n";
    }

    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}