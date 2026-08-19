#include <iostream>
#include <string>
using namespace std;

string arr[101][101];
int N, M;
// n r = n-1 r + n-1 r-1
void init() { cin >> N >> M; }

string sum(string num1, string num2) {
    string ret = "";
    int size = max(num1.size(), num2.size());
    int total = 0;

    for (int i = 0; i < size||total; i++) {
        if (num1.size() > i)
            total += num1[i] - '0';
        if (num2.size() > i)
            total += num2[i] - '0';
        ret += total % 10 + '0';
        total /= 10;
    }
    return ret;
}

string ncm(int n, int m) {
    if (n == m || m == 0)
        return "1";
    if (!arr[n][m].empty())
        return arr[n][m];
    else
        return arr[n][m] = sum(ncm(n - 1, m),ncm(n - 1, m - 1));
}

void solve() {
    ncm(N, M);
    for (int i = arr[N][M].size() - 1; i >= 0; i--)
        cout << arr[N][M][i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();

    return 0;
}