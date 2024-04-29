#include <iostream>

using namespace std;
int A, I;
void init() { cin >> A >> I; }

void solve() { cout << A * (I - 1) + 1; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}