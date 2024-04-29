#include <iostream>
using namespace std;

int a,b,c;
void init() {
    cin >> a >> b;
    c = a+b;
}

void solve() {
    cout << (a+1)*(b+1);
}

int main() {
     ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}