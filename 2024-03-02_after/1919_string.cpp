#include <iostream>
#include <string>

using namespace std;

string s[2];
int arr[2][26];
void init() { cin >> s[0] >> s[1]; }

void solve() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < s[i].size(); j++) {
            arr[i][s[i][j] - 'a']++;
        }
    }
    int answer = 0;
    for (int i = 0; i < 26; i++) {
        answer += arr[0][i] > arr[1][i] ? arr[0][i] - arr[1][i] : arr[1][i] - arr[0][i];
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}