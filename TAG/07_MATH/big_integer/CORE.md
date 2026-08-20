# 큰 수 연산 핵심

## 1. 한 문장 기억

자료형에 담기지 않는 정수는 문자열을 낮은 자리부터 저장하고, 초등학교식 자리 연산과 올림을 그대로 구현한다.

## 2. 언제 꺼내는가

- 정답 자릿수가 `long long` 범위를 넘고 모듈러를 취할 수 없다.
- 덧셈·뺄셈·곱셈 결과 전체를 출력해야 한다.
- 큰 수 DP에서 상태값끼리 정확히 더해야 한다.

## 3. 핵심 상태 / 불변식

- 사용자 코드처럼 숫자 문자열을 뒤집으면 인덱스 0이 일의 자리다.
- 각 반복이 끝날 때 `result[0..i]`는 확정된 낮은 자리이고 `carry`만 다음 자리로 넘어간다.
- 내부 표현은 뒤집힌 문자열로 유지하고 출력할 때만 역순으로 읽는다.

## 4. C++ 최소 구현 골격

```cpp
// a, b는 낮은 자리부터 저장된 문자열
string addReversed(const string& a, const string& b) {
    string result;
    int carry = 0;
    int n = max(a.size(), b.size());
    for (int i = 0; i < n || carry; ++i) {
        int sum = carry;
        if (i < (int)a.size()) sum += a[i] - '0';
        if (i < (int)b.size()) sum += b[i] - '0';
        result.push_back(char('0' + sum % 10));
        carry = sum / 10;
    }
    return result;
}

reverse(a.begin(), a.end());
reverse(b.begin(), b.end());
string result = addReversed(a, b);
for (auto it = result.rbegin(); it != result.rend(); ++it) cout << *it;
```

## 5. 빈 화면 구현 순서

1. 입력을 문자열로 받고 내부 자리 방향을 정한다.
2. 한 자리 합 `digitA + digitB + carry`를 쓴다.
3. `% 10`은 결과 자리, `/ 10`은 다음 올림으로 분리한다.
4. 두 문자열이 끝난 뒤 남은 `carry`까지 처리한다.
5. 큰 수 연산 함수를 DP나 조합 점화식에 연결한다.
6. `0+0`, 자릿수가 다른 수, 마지막 올림이 생기는 수로 검사한다.

## 6. 자주 틀리는 지점

- 내부 표현의 방향이 섞여 한 피연산자만 뒤집는 실수.
- 긴 쪽 문자열이 끝날 때까지만 돌고 마지막 `carry`를 버리는 실수.
- 재귀 조합에서 기저값 `"1"`의 방향과 저장 형식을 다르게 두는 실수.
- 결과가 0일 때 빈 문자열을 반환하는 실수.

## 7. 내 코드에서 다시 보기

- [15353.cpp](./15353.cpp): 두 큰 정수를 뒤집어 자리별로 더하는 최소 형태
- [10826.cpp](./10826.cpp): 같은 덧셈을 피보나치 DP에 연결
- [2407.cpp](./2407.cpp): 파스칼 점화식과 문자열 덧셈을 결합한 큰 조합

