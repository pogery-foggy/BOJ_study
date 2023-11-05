#include <iostream>

using namespace std;

void init() {}

void solve() {
    int N;
    cin >> N;
    if (N % 2)
        cout << "Goose";
    else
        cout << "Duck";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}