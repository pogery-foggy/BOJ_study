#include <iostream>
#include <string>
using namespace std;

int S, K, H;
void init() { cin >> S >> K >> H; }

void solve() {
    if (S + K + H < 100) {
        int mini = min(S, min(K, H));
        if (mini == S) {
            cout << "Soongsil";
        } else if (mini == K) {
            cout << "Korea";
        } else {
            cout << "Hanyang";
        }
    } else {
        cout << "OK";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}