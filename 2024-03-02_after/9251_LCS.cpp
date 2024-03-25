#include <iostream>
#include <string>
#include <algorithm>
#define MAX_N 1000
using namespace std;

int arr[MAX_N + 1][MAX_N + 1];
string s1, s2;
void init() {
    cin >> s1 >> s2;
}


void solve() {
    for (int i = 1; i <= s1.size(); i++) {
        for (int j = 1; j <= s2.size(); j++) {
            if (s1[i - 1] == s2[j - 1]) {
                arr[i][j] = arr[i - 1][j - 1] + 1;
            }
            else {
                arr[i][j] = max(arr[i][j - 1], arr[i - 1][j]);
            }
        }
    }
    cout << arr[s1.size()][s2.size()];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();

    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}