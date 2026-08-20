#include <iostream>
#include <string>
using namespace std;
int N, A, B;
string s;
void init() { cin >> N >> s; }

void solve() {
    for (auto a : s) {
        if (a == 'A')
            A++;
        else
            B++;
    }
    if (A > B)
        cout << "A";
    else if (A < B)
        cout << "B";
    else
        cout << "Tie";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}