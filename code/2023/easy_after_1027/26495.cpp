#include <iostream>
#include <string>
using namespace std;

char arr[5][50] = {"0000    1 2222 3333 4  4 5555 6666 7777 8888 9999", "0  0    1    2    3 4  4 5    6       7 8  8 9  9",
                   "0  0    1 2222 3333 4444 5555 6666    7 8888 9999", "0  0    1 2       3    4    5 6  6    7 8  8    9",
                   "0000    1 2222 3333    4 5555 6666    7 8888    9"};

string N;
void init() { cin >> N; }

void print_num(int cur) {
    for (int i = 0; i < 5; i++) {
        for (int j = (cur * 5); j < (cur * 5) + 4; j++) {
            cout << arr[i][j];
            if (i == 3 && j == 2 * 5) {
                i = 4;
                j = cur * 5 - 1;
                cout << "\n";
                continue;
            }
            if (i == 1 && j == 5 * 5) {
                i = 2;
                j = cur * 5 - 1;
                cout << "\n";
                continue;
            }
            if (i == 1 && j == 6 * 5) {
                i = 2;
                j = cur * 5 - 1;
                cout << "\n";
                continue;
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

void solve() {
    for (int i = 0; i < N.size(); i++) {
        int cur = N[i] - '0';
        print_num(cur);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}