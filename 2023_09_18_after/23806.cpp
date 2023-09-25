#include <iostream>

using namespace std;
int n;

void init() { cin >> n; }

void print_ggggg() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n * 5; j++) {
            cout << "@";
        }
        cout << "\n";
    }
}
void print_gbbbg() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "@";
        }
        for (int j = 0; j < n; j++) {
            cout << " ";
        }
        for (int j = 0; j < n; j++) {
            cout << " ";
        }
        for (int j = 0; j < n; j++) {
            cout << " ";
        }
        for (int j = 0; j < n; j++) {
            cout << "@";
        }
        cout << "\n";
    }
}
void solve() {
    print_ggggg();
    print_gbbbg();
    print_gbbbg();
    print_gbbbg();
    print_ggggg();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}