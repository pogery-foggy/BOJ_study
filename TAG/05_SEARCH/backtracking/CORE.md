# 백트래킹 핵심

## 1. 한 문장 기억

선택 하나를 적용하고 재귀로 내려간 뒤 반드시 원상복구하면서, 더 이상 답이 될 수 없는 가지는 즉시 끊는다.

## 2. 언제 꺼내는가

- 답이 순열·조합·배치처럼 여러 선택의 연속이고 제한이 작다.
- 모든 경우를 보되 `visited`, 중복 선택, 충돌 조건으로 상당수 가지를 줄일 수 있다.
- “현재 선택까지는 유효한가?”를 재귀 중간에 판단할 수 있다.

## 3. 핵심 상태 / 불변식

- `depth`: 지금까지 확정한 선택 수. `dfs(depth)` 진입 시 앞의 `depth`개는 모두 유효하다.
- `path`: 현재 답 후보. 진입 전 `push`, 복귀 직후 `pop`이 한 쌍이다.
- `used` 또는 충돌 배열: 현재 경로가 점유한 것만 `true`다.
- 같은 깊이의 같은 값은 한 번만 고른다. 정렬 후 `last`로 건너뛰면 중복 수열을 막을 수 있다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [9663.cpp](./9663.cpp)의 전역 고정 배열, `put_queen`/`erase_queen` 함수 분리, `dfs(y)` 재귀, `init()` → `solve()` 구조를 축약했다.

```cpp
#define MAX_N 15

int N, cnt = 0;
bool con_x[MAX_N], con_cross_up[2 * MAX_N + 1], con_cross_down[2 * MAX_N + 1];

void put_queen(int x, int y) {
    con_x[x] = true;
    con_cross_up[x + y] = true;
    con_cross_down[y - x + MAX_N] = true;
}

void erase_queen(int x, int y) {
    con_x[x] = false;
    con_cross_up[x + y] = false;
    con_cross_down[y - x + MAX_N] = false;
}

void dfs(int y) {
    if (y == N) {
        cnt++;
        return;
    }
    for (int x = 0; x < N; x++) {
        if (con_x[x])
            continue;
        if (con_cross_up[x + y])
            continue;
        if (con_cross_down[y - x + MAX_N])
            continue;
        put_queen(x, y);
        dfs(y + 1);
        erase_queen(x, y);
    }
}

void init() { cin >> N; }

void solve() {
    dfs(0);
    cout << cnt;
}
```

수열 문제에서는 [15654.cpp](./15654.cpp)처럼 전역 `is_visit[]`, `answer`를 켰다가 재귀 복귀 직후 원상복구한다.

## 5. 빈 화면 구현 순서

1. 한 재귀 단계가 결정할 대상과 `depth`의 의미를 한 줄로 적는다.
2. 완성 조건과 답 처리부터 쓴다.
3. 가능한 선택을 도는 반복문을 쓴다.
4. 선택 불가 조건을 `continue`로 앞에 모은다.
5. `선택 → 재귀 → 복구` 세 줄을 대칭으로 쓴다.
6. 작은 입력을 손으로 그려 중복과 복구 여부를 확인한다.

## 6. 자주 틀리는 지점

- 기저 조건에서 답을 처리한 뒤 `return`하지 않아 불필요하게 더 내려가는 실수.
- 값 중복과 인덱스 중복을 혼동하는 실수. `used`는 원소, `last`는 같은 깊이의 같은 값이다.
- 재귀 후 `used=false`, `pop_back()` 또는 충돌 표시 해제를 빠뜨리는 실수.
- 대각선 인덱스 `y-x`가 음수가 되므로 충분한 오프셋이 필요하다.

## 7. 내 코드에서 다시 보기

- [15654.cpp](./15654.cpp): 정렬, `visited`, 깊이별 `last`, 선택/복구의 기본형
- [9663.cpp](./9663.cpp): 열과 두 대각선 충돌을 O(1) 상태로 바꾼 N-Queen
