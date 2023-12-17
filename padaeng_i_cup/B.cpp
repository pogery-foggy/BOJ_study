#include <iostream>

using namespace std;
int N, M;
int ny, mx;
int two_number; // bool
char arr[600][600];

void correct(int y, int x) {
    // y
    for (int i = x + 1; i <= x + 5 + two_number; i++) {
        arr[y][i] = '*';
    }
    // y+1
    arr[y + 1][x] = '*';
    arr[y + 1][x + 6 + two_number] = '*';

    // y+2
    for (int i = x + 1; i <= x + 5 + two_number; i++) {
        arr[y + 2][i] = '*';
    }
}

void wrong(int y, int x) {
    arr[y][x + 3] = '/';
    arr[y + 1][x + 2] = '/';
    arr[y + 2][x + 1] = '/';
}
void init() {
    cin >> N >> M;
    ny = N * 3;
    mx = M * 8;
    for (int i = 0; i < ny; i++) {
        for (int j = 0; j < mx; j++) {
            cin >> arr[i][j];
        }
    }
}
bool is_check(int y, int x) {
    two_number = 0;
    x = x + 1;
    y = y + 1;
    int num1 = arr[y][x] - '0';
    char oper = arr[y][x + 1];
    int num2 = arr[y][x + 2] - '0';
    int num3 = arr[y][x + 4] - '0';
    if (arr[y][x + 5] >= '0' && arr[y][x + 5] <= '9') {
        num3 *= 10;
        num3 += arr[y][x + 5] - '0';
        two_number = 1;
    }

    if (oper == '+') {
        return num3 == num1 + num2;
    } else if (oper == '-') {
        return num3 == num1 - num2;
    } else if (oper == '/') {
        return num1 == num3 * num2;
    } else {
        return num3 == num1 * num2;
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            bool answer = is_check(i * 3, j * 8);
            if (answer)
                correct(i * 3, j * 8);
            else
                wrong(i * 3, j * 8);
        }
    }

    for (int i = 0; i < ny; i++) {
        for (int j = 0; j < mx; j++) {
            cout << arr[i][j];
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}