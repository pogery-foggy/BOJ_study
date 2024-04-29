#include <iostream>
#include <string>
using namespace std;
int N;
string s;
char alp[3] = {'J', 'O', 'I'};
int arr[3];
void init() { cin >> N >> s; }

void solve() {
    for (auto a : s) {
        if (a == 'J')
            arr[0]++;
        else if (a == 'O')
            arr[1]++;
        else
            arr[2]++;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < arr[i]; j++) {
            cout << alp[i];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}