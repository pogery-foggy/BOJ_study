#include <iostream>

using namespace std;

int arr[10001];
int maxi = -1, N;
void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        arr[a]++;
    }
}

void solve() {
    for (int i = 1; i <= 10000; i++) {
        maxi = maxi > arr[i] ? maxi : arr[i];
    }
    cout << maxi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}