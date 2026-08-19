#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool flag;
int N;
int arr[26];
void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        string tmp;
        cin >> tmp;
        arr[tmp[0] - 'a']++;
    }
}

void solve() {
    for (int i = 0; i < 26; i++) {
        if (arr[i] >= 5) {
            cout << char(i + 'a');
            flag = true;
        }
    }
    if (!flag)
        cout << "PREDAJA";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}