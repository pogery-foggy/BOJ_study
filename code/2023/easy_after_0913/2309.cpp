#include <iostream>

using namespace std;

int arr[9], total;
bool plag[9];
void sorting() {
    // 01 12 23 34 45 56 67 78 89
    // 01 12 23 34 45 56 67 78
    for (int i = 0; i < 9; i++) {
        for (int j = 1; j < 9 - i; j++) {
            if (arr[j - 1] > arr[j]) {
                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void init() {
    for (int i = 0; i < 9; i++) {
        cin >> arr[i];
    }
    sorting();
    for (int i = 0; i < 9; i++) {
        total += arr[i];
    }
}
void print_kee(int a, int b) {
    for (int i = 0; i < 9; i++) {
        if (i != a && i != b)
            cout << arr[i] << "\n";
    }
}

void solve() {
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (total - arr[i] - arr[j] == 100) {
                print_kee(i, j);
                return;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}