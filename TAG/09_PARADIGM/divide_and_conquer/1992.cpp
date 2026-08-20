#include <iostream>
#include <string>
using namespace std;

int map[64][64], N;

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char a;
            cin >> a;
            map[j][i] = a - '0';
        }
    }
}

string divide(int x_s, int x_e, int y_s, int y_e) {
    if (x_s == x_e) {
        return to_string(map[x_s][y_s]);
    }
    int x_mid = (x_s + x_e) >> 1;
    int y_mid = (y_s + y_e) >> 1;
    string value1 = divide(x_s, x_mid, y_s, y_mid);
    string value2 = divide(x_mid + 1, x_e, y_s, y_mid);
    string value3 = divide(x_s, x_mid, y_mid + 1, y_e);
    string value4 = divide(x_mid + 1, x_e, y_mid + 1, y_e);
    if (value1 == value2 && value3 == value4 && value1 == value3) {
        if (value1.size() == 1 && value2.size() == 1 && value3.size() == 1 && value4.size() == 1)
            return value1;
        else
            return "(" + value1 + value2 + value3 + value4 + ")";
    }
    else {
        return "(" + value1 + value2 + value3 + value4 + ")";
    }
}

void solve() {
    cout << divide(0, N - 1, 0, N - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();


    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}