#include <iostream>

using namespace std;
long long arr[10];
long long N, s, ten;
void init() {
    cin >> N;
    s = ten = 1;
}

// 얼마나 등장할지, 그래 이 방법이다. dec에는 10이 계속 곱해질 예정
void where(int num, long long dec) {
    while (num > 0) {
        arr[num % 10] += dec;
        num = num / 10;
    }
}

void solve() {
    while (s <= N) {
        while (s % 10 != 0 && s <= N) {
            where(s, ten);
            s += 1;
        }

        if (s > N)
            break;

        while (N % 10 != 9 && s <= N) {
            where(N, ten);
            N -= 1;
        }

        s /= 10;
        N /= 10;
        // 1230 ~1200 1,2 * 31
        long long cnt = N - s + 1;

        for (int i = 0; i < 10; i++)
            arr[i] += cnt * ten;

        ten *= 10;
    }

    for (int i = 0; i < 10; i++)
        cout << arr[i] << " ";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}