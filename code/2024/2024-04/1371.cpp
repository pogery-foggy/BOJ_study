#include <iostream>

using namespace std;
char c;
int maxi;
int arr[26];
void init() {
    while (cin >> c) {
        if ('a' <= c && c <= 'z') {
            arr[c - 'a']++;
        }
    }
}

void solve() {
    for (int i = 0; i < 26; i++) {
        maxi = maxi > arr[i] ? maxi : arr[i];
    }
    for (int i = 0; i < 26; i++) {
        if (arr[i] == maxi)
            cout << char(i + 'a');
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}