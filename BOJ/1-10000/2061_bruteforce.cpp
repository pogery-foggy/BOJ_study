#include <iostream>
#include <string>
using namespace std;
int L, answer = INT32_MAX;
int isPrime[10000000];
string K;

void init() {
    cin >> K >> L;
    for (int i = 2; i * i <= L; i++) {
        if (isPrime[i] == false) {
            for (int j = i * i; j <= L; j += i) {
                isPrime[j] = true;
            }
        }
    }
}

void solve() {
    for (int i = 2; i < L; i++) {
        int temp = 0;
        if (isPrime[i])
            continue;
        for (int j = 0; j < K.size(); j++) {
            temp = temp * 10 + K[j] - '0';
            temp %= i;
        }
        if (temp==0) {
            answer = i;
            break;
        }
    }

    if (answer < L)
        cout << "BAD " << answer;
    else
        cout << "GOOD";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}