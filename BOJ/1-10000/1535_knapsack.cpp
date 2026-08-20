#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N;
int human[21][2]; // lose hp, be happy;
int table[21][100];

void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> human[i][0];
    }
    for (int i = 1; i <= N; i++) {
        cin >> human[i][1];
    }
}

void solve() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= 100; j++) {
            if (human[i][0] < j) {
                table[i][j] = max(table[i - 1][j], table[i - 1][j - human[i][0]] + human[i][1]);
            } else
                table[i][j] = table[i - 1][j];
        }
    }
    cout << table[N][100];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}