# Convex Hull 기억 복원

## 한 문장 기억

기준점에서 각도순으로 점을 보고, 마지막 두 점과 새 점이 원하는 회전 방향을 깨면 가운데 점을 버린다.

## 언제 꺼내는가

- 모든 점을 감싸는 가장 바깥 다각형이 필요할 때
- 울타리 길이, 바깥 점 개수, 다각형 넓이의 전처리가 필요할 때
- 점 집합에서 내부 점을 제거하고 경계만 남기고 싶을 때

## 핵심 상태/불변식

- 사용자 코드의 Graham scan에서는 가장 아래, 같으면 가장 왼쪽 점을 pivot으로 둔다.
- 나머지는 pivot 기준 반시계 각도순, 일직선이면 가까운 순으로 정렬한다.
- hull에는 처리한 점들의 올바른 반시계 볼록 경계만 남는다.
- 끝점만 남길 때 새 점이 `ccw <= 0`이면 마지막 점을 pop한다.

## C++ 최소 구현 골격

```cpp
struct Point { long long x, y; };

long long ccw(Point a, Point b, Point c) {
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}
long long dist2(Point a, Point b) {
    long long x=a.x-b.x, y=a.y-b.y;
    return x*x + y*y;
}

int pivot = min_element(p.begin(), p.end(), [](auto a, auto b) {
    return tie(a.y,a.x) < tie(b.y,b.x);
}) - p.begin();
swap(p[0], p[pivot]);
Point base = p[0];

sort(p.begin()+1, p.end(), [&](Point a, Point b) {
    long long turn = ccw(base,a,b);
    return turn ? turn > 0 : dist2(base,a) < dist2(base,b);
});

vector<Point> hull;
for (Point x : p) {
    while (hull.size() >= 2 &&
           ccw(hull[hull.size()-2], hull.back(), x) <= 0)
        hull.pop_back();
    hull.push_back(x);
}
```

## 빈 화면 구현 순서

1. `Point`, `ccw`, 필요하면 `dist2`를 만든다.
2. pivot 선택 규칙을 문제의 좌표계와 맞춘다.
3. 각도순 comparator와 일직선 tie-break를 쓴다.
4. 정렬된 점을 순서대로 보며 회전 조건이 깨질 동안 pop한다.
5. 문제 요구에 맞춰 경계의 일직선 점 포함 여부와 둘레/넓이를 처리한다.

## 자주 틀리는 지점

- comparator가 캡처한 pivot은 정렬 중 바뀌면 안 되므로 별도 변수에 복사한다.
- 경계의 일직선 점을 포함하면 pop 조건이 `< 0`, 양끝만 포함하면 `<= 0`이다.
- 좌표 곱은 `long long` 범위인지 먼저 계산한다.
- 모든 점이 일직선인 경우와 점이 1~2개인 경우를 따로 확인한다.
- 단순 다각형 순서 문제는 마지막 동일 각도 묶음을 뒤집는 등 hull 자체와 다른 후처리가 필요할 수 있다.

## 대표 코드

- [1708.cpp](1708.cpp) — pivot, 각도 정렬, pop으로 이어지는 Graham scan 기본형
- [3679.cpp](3679.cpp) — 마지막 일직선 묶음을 뒤집어 단순 다각형 순서를 만드는 응용
- [7420.cpp](7420.cpp) — 볼록 껍질 둘레에 원호 길이를 더하는 응용
