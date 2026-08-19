#include <iostream>

using namespace std;

int A, B, total, stack = 1, arr[2001];

void init() {
    cin >> A >> B;
    for (int i = 1; stack < 1001; i++) {
        for (int j = 0; j < i; j++) {
            arr[stack++] = i;
            if (stack == 1001)
                break;
        }
    }
}

void solve() {
    for (int i = A; i <= B; i++) {
        total += arr[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << total;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}