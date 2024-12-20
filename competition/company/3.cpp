#include <cstdio>
#include <iostream>

using namespace std;

int prefix_sum[1921][1081];

void init() {
    // txt파일이랑 소스코드랑 같이 두면 됩니다.
    freopen("input3.txt", "r", stdin);
    int sx, sy, ex, ey;
    while (cin >> sx >> sy >> ex >> ey) {
        prefix_sum[sx][sy] += 1;
        prefix_sum[sx][ey] -= 1;
        prefix_sum[ex][sy] -= 1;
        prefix_sum[ex][ey] += 1;
    }
}

void solve() {
    int sum = 0;

    for (int i = 0; i <= 1920; i++) {
        for (int j = 1; j <= 1080; j++) {
            prefix_sum[i][j] += prefix_sum[i][j - 1];
        }
    }

    for (int j = 0; j <= 1080; j++) {
        for (int i = 1; i <= 1920; i++) {
            prefix_sum[i][j] += prefix_sum[i - 1][j];
        }
    }

    for (int i = 0; i <= 1920; i++) {
        for (int j = 0; j <= 1080; j++) {
            if (prefix_sum[i][j])
                sum++;
        }
    }
    cout << sum;
}

int main() {
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}