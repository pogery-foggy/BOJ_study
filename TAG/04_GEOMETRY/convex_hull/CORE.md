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

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [1708.cpp](1708.cpp)의 `Point`, 전역 `stars`, 기준점을 `stars[0]`으로 직접 참조하는 `compare`, 수동 교환, `vector<Point> convex`와 인덱스 반복문을 그대로 축약했다.

```cpp
struct Point{
    long long x, y;
};
vector<Point> stars;
int N;

long long ccw(Point a, Point b, Point c){
    long long x1 = b.x - a.x;
    long long y1 = b.y - a.y;
    long long x2 = c.x - a.x;
    long long y2 = c.y - a.y;
    return x1 * y2 - x2 * y1;
}

long long dist(Point a, Point b){
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

bool compare(Point a, Point b){
    long long direction = ccw(stars[0], a, b);
    if(direction > 0) return true;
    if(direction < 0) return false;
    return dist(stars[0], a) < dist(stars[0], b);
}

void solve() {
    vector<Point> convex;
    convex.push_back(stars[0]);
    convex.push_back(stars[1]);
    for(int i = 2; i < N; i++){
        while(convex.size() >= 2){
            Point a = convex[convex.size() - 2];
            Point b = convex[convex.size() - 1];
            if(ccw(a, b, stars[i]) > 0) break;
            convex.pop_back();
        }
        convex.push_back(stars[i]);
    }
}
```

기준점 선택도 실제 코드처럼 `y`가 작고, 같으면 `x`가 작은 인덱스를 반복문으로 찾아 `stars[0]`과 바꾼 뒤 `sort(stars.begin()+1, stars.end(), compare)`한다.

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
