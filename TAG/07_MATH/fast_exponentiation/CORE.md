# 빠른 거듭제곱 핵심

## 1. 한 문장 기억

지수를 이진수로 보며 밑을 제곱하고, 켜진 비트에 해당하는 값만 답에 곱하면 O(log B)에 거듭제곱할 수 있다.

## 2. 언제 꺼내는가

- 지수 B가 매우 커서 B번 곱할 수 없다.
- 모듈러 거듭제곱, 행렬 거듭제곱, 선형 점화식의 큰 항을 구한다.
- 결합법칙이 성립하는 연산의 반복을 절반씩 줄일 수 있다.

## 3. 핵심 상태 / 불변식

- 반복형에서 항상 `answer * base^exp`가 원래 구하려던 값과 같다.
- `exp`의 현재 최하위 비트가 1이면 현재 `base`를 답에 반영한다.
- 매 단계 `base=base*base`, `exp>>=1`; 모듈러는 곱셈 직후 적용한다.

## 4. C++ 최소 구현 골격

```cpp
long long power(long long base, long long exp, long long mod) {
    long long answer = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1LL) answer = answer * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return answer;
}
```

행렬도 동일하다. `answer`를 단위행렬로 두고 스칼라 곱셈 대신 `mul(answer, base)`, `mul(base, base)`를 호출한다.

## 5. 빈 화면 구현 순서

1. 항등원(숫자는 1, 행렬은 단위행렬)을 만든다.
2. `while (exp>0)`을 쓴다.
3. 홀수 비트면 답에 현재 밑을 곱한다.
4. 밑을 제곱하고 지수를 절반으로 줄인다.
5. 모든 곱셈 위치에 모듈러를 적용한다.
6. 지수 0, 1, 홀수, 짝수를 검사한다.

## 6. 자주 틀리는 지점

- 지수 0에서 답 1을 처리하지 않는 재귀 기저 실수.
- `int * int`가 모듈러 적용 전에 overflow하는 실수.
- 행렬 답의 초기값을 0행렬로 두는 실수.
- 홀수 지수에서 반제곱 값을 두 번 재귀 호출해 O(B)가 되는 실수.

## 7. 내 코드에서 다시 보기

- [1629.cpp](./1629.cpp): 지수를 반으로 나누고 홀수일 때 A를 한 번 더 곱하는 재귀형
- [2749.cpp](./2749.cpp): 큰 피보나치 항을 빠르게 줄이는 응용
- 행렬 반복형은 [../../09_PARADIGM/divide_and_conquer/10830.cpp](../../09_PARADIGM/divide_and_conquer/10830.cpp)에서 확인

