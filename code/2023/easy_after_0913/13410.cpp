#include <iostream>
#define MAX_N 1001
using namespace std;

int N, K;

int arr[MAX_N];

void init() { cin >> N >> K; }

int reverse(int n, int k) {
    int fnd = n * k;
    int result = 0;
    while (fnd > 0) {
        result += fnd % 10;
        result *= 10;
        fnd /= 10;
    }
    result /= 10;
    return result;
}

void solve() {
    for (int i = 1; i <= K; i++) {
        arr[i] = reverse(N, i);
    }
    int maxi = -1;
    for (int i = 1; i <= K; i++) {
        maxi = maxi > arr[i] ? maxi : arr[i];
    }
    cout << maxi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}