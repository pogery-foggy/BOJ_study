# Line Intersection 기억 복원

## 한 문장 기억

각 선분의 양 끝에서 상대 선분의 두 점이 어느 쪽에 있는지 외적 부호로 검사하고, 모두 일직선이면 투영 구간의 겹침을 따로 본다.

## 언제 꺼내는가

- 두 선분이 만나거나 겹치는지 판정할 때
- 교점 좌표를 출력해야 할 때
- 교차하는 선분들을 DSU로 묶는 문제의 기본 판정기로 사용할 때

## 핵심 상태/불변식

- 일반 교차는 `ccw(a,b,c) * ccw(a,b,d) <= 0`과 반대 선분 조건이 모두 성립한다.
- 네 ccw가 모두 0이면 일직선이므로 x와 y 투영 구간이 모두 겹쳐야 한다.
- 교점 좌표는 무한 직선의 행렬식 공식으로 구하되, 겹치는 선분이 한 점에서만 만날 때만 그 점을 출력한다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [17387.cpp](17387.cpp)의 `Point`, 전역 네 끝점, 벡터 성분을 풀어 쓴 `ccw`, 네 방향값을 개별 변수로 저장한 뒤 `cond1`, `cond2`로 판정하는 `solve()`를 그대로 축약했다.

```cpp
struct Point {
    long long x, y;
};
Point a1, b1, a2, b2;

long long ccw(Point a, Point b, Point c) {
    long long x1 = b.x - a.x;
    long long y1 = b.y - a.y;
    long long x2 = c.x - a.x;
    long long y2 = c.y - a.y;
    long long result = x1 * y2 - x2 * y1;
    if (result < 0) return -1;
    else if (result == 0) return 0;
    else return 1;
}

void solve() {
    int L1a2 = ccw(a1, b1, a2);
    int L1b2 = ccw(a1, b1, b2);
    int L2a1 = ccw(a2, b2, a1);
    int L2b1 = ccw(a2, b2, b1);
    int cond1 = L1a2 * L1b2;
    int cond2 = L2a1 * L2b1;

    if (cond1 == 0 && cond2 == 0) {
        if (max(a1.x, b1.x) < min(a2.x, b2.x)
         || max(a2.x, b2.x) < min(a1.x, b1.x)
         || max(a1.y, b1.y) < min(a2.y, b2.y)
         || max(a2.y, b2.y) < min(a1.y, b1.y))
            cout << 0;
        else
            cout << 1;
    } else if (cond1 <= 0 && cond2 <= 0) {
        cout << 1;
    } else {
        cout << 0;
    }
}
```

원본에 주석 처리되어 있던 디버그 `cout`은 골격에 복제하지 않았다. 교점 좌표까지 필요하면 [20149.cpp](20149.cpp)의 실수/정확한 끝점 처리를 이어서 본다.

## 빈 화면 구현 순서

1. `Point`, 64비트 `cross`, 부호 함수부터 만든다.
2. 상대 선분 끝점 네 개의 ccw 부호를 계산한다.
3. 네 값이 모두 0인 일직선 case를 먼저 분리한다.
4. 일직선이면 x·y 투영 구간의 겹침을 `<=`로 확인한다.
5. 그 외에는 두 부호 곱이 각각 0 이하인지 본다.
6. 좌표 출력이 필요하면 유일 교차인지 판정한 뒤 행렬식으로 계산한다.

## 자주 틀리는 지점

- 끝점 접촉도 교차이면 `< 0`이 아니라 `<= 0`이다.
- 일직선인 두 선분은 ccw 곱만으로 겹침 여부를 알 수 없다.
- 좌표별 min/max 정규화 없이 사전순 비교만 하면 수직선분에서 실수하기 쉽다.
- 교점 공식은 분모가 0인 평행/일치 경우에 사용하지 않는다.
- 정수 곱을 먼저 계산한 뒤 `double`에 담으면 이미 overflow할 수 있다.

## 대표 코드

- [17387.cpp](17387.cpp) — 끝점 접촉과 일직선 겹침을 포함한 판정 기본형
- [20149.cpp](20149.cpp) — 판정 뒤 유일 교점 좌표까지 출력하는 구현
- [2162.cpp](2162.cpp) — 교차 판정 결과를 DSU 연결로 확장한 응용
