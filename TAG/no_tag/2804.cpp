#include <iostream>
#include <string>
using namespace std;
string a, b;
char map[31][31];
int ch[26];
int cross_a, cross_b;
void init() {
    cin >> a >> b;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            if (a[i] == b[j]) {
                cross_a = j;
                cross_b = i;
                return;
            }
        }
    }
}

void solve() {
    for (int i = 0; i < b.size(); i++) {
        for (int j = 0; j < a.size(); j++) {
            if (j == cross_b)
                cout << b[i];
            else if (i == cross_a)
                cout << a[j];
            else
                cout << ".";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}