#include <iostream>

using namespace std;

int A, B, C;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void init() { cin >> A >> B >> C; }

void solve() {
    if (A > B)
        swap(A, B);
    if (B > C)
        swap(B, C);
    if (A > B)
        swap(A, B);

    cout << B;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}