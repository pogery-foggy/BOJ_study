int power(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { // 홀수 지수
            result *= base;
        }
        base *= base; // 지수를 제곱
        exp /= 2; // 지수를 절반으로 줄임
    }
    return result;
}