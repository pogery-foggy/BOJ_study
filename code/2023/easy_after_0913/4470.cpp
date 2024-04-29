#include <iostream>
#include <string>
using namespace std;
string s;
int N;
void init() {
    cin >> N;
    cin.ignore();
    for (int i = 0; i < N; i++) {
        getline(cin, s);
        cout << i+1 << ". " << s << "\n";
    }
}

void solve() {}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}