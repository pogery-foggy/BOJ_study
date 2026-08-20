# Geometry 기본 도구 기억 복원

## 한 문장 기억

그림을 좌표의 차·제곱거리·외적으로 바꾸고, 루트나 실수 계산은 마지막 출력 직전까지 미룬다.

## 언제 꺼내는가

- 세 점의 방향, 점이 원 안/밖인지, 거리·둘레·넓이를 판정할 때
- 격자 높이 차이처럼 노출된 면을 직접 세는 문제일 때
- 복잡한 알고리즘보다 정확한 식과 경계 판정이 핵심일 때

## 핵심 상태/불변식

- `cross((b-a),(c-a))`의 양수/0/음수는 반시계/일직선/시계다.
- 점과 원의 관계는 `dx² + dy²`와 `r²`을 비교하면 루트가 필요 없다.
- 두 점이 어떤 경계를 서로 다른 상태로 통과하는지는 `inside(start) != inside(end)`로 표현한다.
- 격자 입체의 옆면은 경계 높이와 이웃보다 증가한 높이만 합치면 중복 없이 센다.

## C++ 최소 구현 골격

```cpp
struct Point { long long x, y; };

long long cross(Point a, Point b, Point c) {
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

int ccw(Point a, Point b, Point c) {
    long long v = cross(a,b,c);
    return (v > 0) - (v < 0);
}

bool inside_circle(Point p, Point center, long long r) {
    long long dx=p.x-center.x, dy=p.y-center.y;
    return dx*dx + dy*dy < r*r;
}

if (inside_circle(start,c,r) != inside_circle(finish,c,r))
    ++crossed_boundaries;
```

## 빈 화면 구현 순서

1. 입력 좌표와 중간 곱의 최댓값을 계산해 자료형을 정한다.
2. 그림의 조건을 벡터 차 또는 제곱거리 식으로 옮긴다.
3. `<`, `<=`, `==` 중 경계 포함 여부를 문제 문장에 맞춘다.
4. 판정 함수를 먼저 만들고 작은 축 정렬 예제로 검증한다.
5. 실수 출력이 필요할 때만 `sqrt`, `acos`, `double`을 사용한다.

## 자주 틀리는 지점

- 외적은 `(b-a) × (c-a)` 순서가 바뀌면 부호도 바뀐다.
- 좌표가 `int`여도 곱하기 전에 `long long`으로 승격되어야 한다.
- 원 위를 내부로 볼지 외부로 볼지 문제 조건을 확인한다.
- `M_PI` 사용 가능 여부와 출력 오차 조건을 확인한다.
- 3차원 겉넓이는 보이는 면을 직접 세되 맞닿은 면을 두 번 빼지 않는다.

## 대표 코드

- [11758.cpp](11758.cpp) — 외적 부호로 방향을 판정하는 최소 예제
- [1004.cpp](1004.cpp) — 출발점과 도착점의 원 내부 상태 XOR
- [16931.cpp](16931.cpp) — 행·열 높이 증가량으로 노출 면을 세는 구현
