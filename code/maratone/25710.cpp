#include <iostream>

using namespace std;
int arr[1000];
int N, maxi;
int sum(int x) {
    int ret = 0;
    while (x > 0) {
        ret += x % 10;
        x /= 10;
    }
    return ret;
}
void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        arr[a]++;
    }
}

void solve() {

    for (int i = 1; i <= 999; i++) {
        for (int j = i; j <= 999; j++) {
            if (arr[i] > 0 && arr[j] > 0) {
                if (j == i && arr[i] < 2)
                    continue;
                int a = sum(i * j);
                maxi = maxi > a ? maxi : a;
            }
        }
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