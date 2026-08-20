# 좌표 압축 핵심

## 1. 한 문장 기억

값의 크기 자체가 아니라 정렬 순서만 필요하면, 중복을 제거한 정렬 배열에서 각 값을 순위 인덱스로 바꾼다.

## 2. 언제 꺼내는가

- 좌표 범위는 매우 크지만 실제 등장하는 값은 N개뿐이다.
- 세그먼트 트리·Fenwick 트리의 인덱스로 값의 대소관계만 보존하면 된다.
- 각 값보다 작은 서로 다른 값의 개수를 구한다.

## 3. 핵심 상태 / 불변식

- `compressed`는 원본 전체를 복사해 정렬하고 중복 제거한 배열이다.
- `lower_bound(compressed, x)`의 인덱스는 x보다 작은 서로 다른 값의 수다.
- `x<y`이면 압축 후 인덱스도 반드시 작다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [18870.cpp](./18870.cpp)의 전역 `arr, cpy`, 입력값을 두 벡터에 동시에 `push_back`, `solve()`에서 `sort`/`unique`, 범위 `for (auto ans : arr)` 출력 구조를 그대로 축약했다. 이 폴더의 실제 풀이를 그대로 기준으로 삼았다.

```cpp
vector<int> arr, cpy;
int N;

void init() {
    int user_in;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> user_in;
        arr.push_back(user_in);
        cpy.push_back(user_in);
    }
}

void solve() {
    sort(cpy.begin(), cpy.end());
    cpy.erase(unique(cpy.begin(), cpy.end()), cpy.end());
    for (auto ans : arr)
        cout << lower_bound(cpy.begin(), cpy.end(), ans) - cpy.begin() << " ";
}
```

좌표 값 자체가 `int` 범위를 넘는 문제에서만 두 벡터의 원소형을 함께 `long long`으로 바꾼다.

## 5. 빈 화면 구현 순서

1. 원본 순서를 보존할 배열과 정렬용 복사본을 분리한다.
2. 복사본을 정렬한다.
3. `erase(unique(...), end())`로 중복을 실제로 제거한다.
4. 원본을 순회하며 `lower_bound` 인덱스를 구한다.
5. 이후 자료구조가 1-indexed면 `rank+1`로 변환한다.

## 6. 자주 틀리는 지점

- 원본 자체를 정렬해 출력 순서를 잃는 실수.
- `unique`만 호출하고 `erase`하지 않는 실수.
- 중복값마다 다른 순위를 부여하는 실수.
- 세그먼트 트리 범위가 `[0,U-1]`인지 `[1,U]`인지 섞는 실수.

## 7. 내 코드에서 다시 보기

- [18870.cpp](./18870.cpp): 복사·정렬·중복 제거·`lower_bound`의 정석 흐름
- 응용은 [../inversion_counting/2517.cpp](../inversion_counting/2517.cpp): 값을 순위로 바꾼 뒤 구간 개수 자료구조에 연결
