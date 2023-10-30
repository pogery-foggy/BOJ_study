#include <iostream>

using namespace std;
int N;
int arr[51], l, r, lmaxi, rmaxi;
void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    l = 1, r = 1;
    lmaxi = arr[0], rmaxi = arr[N - 1];
}

void solve() {
    for (int i = 0; i < N - 1; i++) {
        if (lmaxi < arr[i + 1]) {
            l++;
            lmaxi = arr[i + 1];
        }
    }
    for (int i = N - 1; i > 0; i--) {
        if (rmaxi < arr[i - 1]) {
            r++;
            rmaxi = arr[i - 1];
        }
    }
    cout << l << "\n" << r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}