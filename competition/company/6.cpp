#include <iostream>

using namespace std;

long long validS, validE;
long long fibo[60];
long long sum = 0;

void init() {
    validS = 12345678999;
    validE = 99987654321;
    fibo[1] = 1;
    fibo[2] = 1;
}

void solve() {
    // validE < fibo[55]
    for (int i = 3; i < 60; i++) {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
        if (validS <= fibo[i] && fibo[i] <= validE)
            sum += fibo[i];
        else if (validE < fibo[i])
            break;
    }
    cout << sum;
}

int main() {
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}