#include <iostream>

using namespace std;
int a, b, c;

int dp[21][21][21];

void init() { cin >> a >> b >> c; }

int w(int x, int y, int z) {
    if (x <= 0 || y <= 0 || z <= 0)
        return 1;
    else if (x > 20 || y > 20 || z > 20)
        return w(20, 20, 20);
    else if (dp[x][y][z])
        return dp[x][y][z];
    else if (x < y && y < z)
        return dp[x][y][z] = w(x, y, z - 1) + w(x, y - 1, z - 1) - w(x, y - 1, z);
    return dp[x][y][z] = w(x - 1, y, z) + w(x - 1, y - 1, z) + w(x - 1, y, z - 1) - w(x - 1, y - 1, z - 1);
}

void solve() { cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c) << "\n"; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (1) {
        init();
        if (a == -1 && b == -1 && c == -1)
            break;
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}