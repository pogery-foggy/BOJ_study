#include <iostream>

// 이항계수
using namespace std;

int B[100][100] = {-1}; // 초기화 필요

int bino1(int n, int r) {
    if (r == 0 or n == r)
        return 1;
    if (B[n][r] != -1)
        return B[n][r];
    B[n][r] = bino1(n - 1, r - 1) + bino1(n - 1, r);
}

int main() {
    /* B[N][R]*/

    return 0;
}