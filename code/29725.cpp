#include <iostream>

using namespace std;

char map[8][8];
int answer;

void check(char a) {
    if (a == 'p')
        answer -= 1;
    else if (a == 'P')
        answer += 1;
    else if (a == 'n' || a == 'b')
        answer -= 3;
    else if (a == 'N' || a == 'B')
        answer += 3;
    else if (a == 'r')
        answer -= 5;
    else if (a == 'R')
        answer += 5;
    else if (a == 'q')
        answer -= 9;
    else if (a == 'Q')
        answer += 9;
}

void init() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> map[i][j];
        }
    }
}

void solve() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            check(map[i][j]);
        }
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}