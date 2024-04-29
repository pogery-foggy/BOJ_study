#include <iostream>

using namespace std;
int arr[9], sum, del1, del2;
void init() {
    for (int i = 0; i < 9; i++) {
        cin >> arr[i];
        sum += arr[i];
    }
}

void solve() {
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (sum - arr[i] - arr[j] == 100) {
                del1 = i;
                del2 = j;
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        if (i != del1 && i != del2)
            cout << arr[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}