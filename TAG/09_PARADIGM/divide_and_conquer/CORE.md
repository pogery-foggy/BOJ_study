# 분할 정복 핵심

## 1. 한 문장 기억

큰 문제를 같은 모양의 작은 문제로 나누고, 기저 결과를 합쳐 원래 문제의 답을 만든다.

## 2. 언제 꺼내는가

- 구간이나 격자를 절반·사분면으로 나눠도 같은 문제가 된다.
- 전체가 균일하면 멈추고 아니면 더 잘게 나눌 수 있다.
- 반복 연산의 크기를 절반씩 줄여 O(log N)에 처리할 수 있다.

## 3. 핵심 상태 / 불변식

- 재귀 함수의 인자는 지금 책임지는 구간/영역 전체를 정확히 표현한다.
- 기저 조건은 더 쪼갤 수 없는 최소 크기다.
- 자식 영역은 부모를 빠짐없이 덮고 서로 겹치지 않는다.
- 반환값은 부모가 결합할 수 있는 완결된 형태다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [1992.cpp](./1992.cpp)의 전역 `map[64][64]`, 네 경계를 받는 `divide`, `>> 1`로 중간점을 만들고 네 재귀 결과를 `value1`~`value4`에 저장하는 구조를 축약했다.

```cpp
int map[64][64], N;

string divide(int x_s, int x_e, int y_s, int y_e) {
    if (x_s == x_e)
        return to_string(map[x_s][y_s]);

    int x_mid = (x_s + x_e) >> 1;
    int y_mid = (y_s + y_e) >> 1;
    string value1 = divide(x_s, x_mid, y_s, y_mid);
    string value2 = divide(x_mid + 1, x_e, y_s, y_mid);
    string value3 = divide(x_s, x_mid, y_mid + 1, y_e);
    string value4 = divide(x_mid + 1, x_e, y_mid + 1, y_e);

    if (value1 == value2 && value3 == value4 && value1 == value3) {
        if (value1.size() == 1 && value2.size() == 1
            && value3.size() == 1 && value4.size() == 1)
            return value1;
        else
            return "(" + value1 + value2 + value3 + value4 + ")";
    }
    else
        return "(" + value1 + value2 + value3 + value4 + ")";
}

void solve() { cout << divide(0, N - 1, 0, N - 1); }
```

네 결과가 같아도 이미 괄호로 묶인 문자열이면 한 글자로 압축하지 않는 원본의 중첩 조건과 `value1`~`value4` 변수명을 그대로 두었다. 지수 분할은 [10830.cpp](./10830.cpp)처럼 `typedef long long ll`, 전역 배열, `mul()`과 `B >>= 1`을 사용한다.

## 5. 빈 화면 구현 순서

1. 재귀 함수가 받는 영역과 반환값의 뜻을 정한다.
2. 크기 1 또는 지수 0/1 기저를 먼저 쓴다.
3. 부모를 어떻게 나눌지 좌표와 크기로 적는다.
4. 각 자식을 한 번씩 호출한다.
5. 자식 결과가 합쳐지는 조건과 순서를 구현한다.
6. 최소 크기와 한 번만 분할되는 크기로 검사한다.

## 6. 자주 틀리는 지점

- `[s,e]`와 `[s,e)`를 섞어 영역이 겹치거나 빠지는 실수.
- 압축된 자식 문자열끼리 같은 값처럼 보여도 실제 단일값인지 확인하지 않는 실수.
- 같은 재귀 결과를 두 번 호출해 시간복잡도가 다시 커지는 실수.
- 행렬 곱에서 임시 배열 없이 입력 행렬을 덮어써 아직 필요한 값을 잃는 실수.

## 7. 내 코드에서 다시 보기

- [1992.cpp](./1992.cpp): 네 사분면을 재귀적으로 압축하고 결과 문자열을 결합
- [2630.cpp](./2630.cpp): 영역이 같은 색인지 판단한 뒤 사분할하는 기본형
- [10830.cpp](./10830.cpp): 지수 비트를 절반씩 줄이는 행렬 거듭제곱
