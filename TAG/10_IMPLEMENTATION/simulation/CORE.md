# 시뮬레이션 핵심

## 1. 한 문장 기억

현재 상태를 완전히 표현하고, 문제에 적힌 한 턴의 판정 순서대로 “결정한 뒤 한 번에 갱신”한다.

## 2. 언제 꺼내는가

- 로봇 이동, 회전, 구름·격자 변화처럼 시간 순서가 답을 결정한다.
- 상태 종류는 유한하지만 규칙이 여러 단계로 이어진다.
- 최적화보다 정확한 턴 재현이 핵심이다.

## 3. 핵심 상태 / 불변식

- 루프 시작 시 `(y,x,dir)`와 지도는 직전 턴까지의 결과다.
- 방향 배열의 순서를 하나로 고정하고 회전을 모듈러 연산으로 처리한다.
- 연쇄 회전처럼 동시에 변하는 값은 먼저 `next`/`willMove`에 결정하고 나중에 적용한다.
- 벽과 방문·청소 상태는 서로 다른 의미라면 배열도 분리한다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [14503.cpp](./14503.cpp)의 전역 `map`/`is_clean`, 대문자 위치·방향 `R,C,D`, `dx`/`dy`, 주변 상태를 확인하는 `surround`, `while (1)` 안의 문제 조건 순서 그대로인 분기를 축약했다.

```cpp
#define CLEAR 1
#define WALL 1

int N, M, R, C, D;
int map[51][51], is_clean[51][51];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int cleaning = 0;

bool surround(int y, int x) {
    bool need_clean = false;
    for (int i = 0; i < 4; i++) {
        if (!is_clean[y + dy[i]][x + dx[i]])
            need_clean = true;
    }
    return need_clean;
}

void solve() {
    int y = R, x = C;
    is_clean[y][x] = CLEAR;
    cleaning++;

    while (1) {
        if (is_clean[y][x] != CLEAR) {
            is_clean[y][x] = CLEAR;
            cleaning++;
        }

        bool dirty = surround(y, x);
        if (!dirty) {
            int back = (D + 2) % 4;
            int nx = x + dx[back], ny = y + dy[back];
            if (map[ny][nx] != WALL) {
                x = nx;
                y = ny;
            }
            else
                break;
        } else {
            D = (D + 3) % 4;
            int nx = x + dx[D], ny = y + dy[D];
            if (is_clean[ny][nx] != CLEAR) {
                x = nx;
                y = ny;
            }
        }
    }
    cout << cleaning;
}
```

`init()`에서 원본처럼 벽을 `is_clean=CLEAR`로 함께 표시해야 `surround`가 벽을 청소 후보로 세지 않는다. [14891.cpp](./14891.cpp)의 톱니 상태·재귀 전파 방식은 참고할 수 있지만, 그 파일에 남은 톱니 비트 출력·`cur/dir`·구분선 디버그 출력은 골격에 복제하지 않았다.

## 5. 빈 화면 구현 순서

1. 상태를 위치·방향·지도·보조 배열로 모두 나열한다.
2. 방향 번호와 `dx/dy`를 그림으로 고정한다.
3. 한 턴의 규칙을 문제 순서대로 번호 매긴다.
4. 각 규칙을 조건/결정 단계로 구현한다.
5. 여러 객체가 동시에 변하면 먼저 변화량을 저장하고 일괄 반영한다.
6. 정지 조건과 무한 루프 가능성을 마지막에 확인한다.

## 6. 자주 틀리는 지점

- `map[y][x]`와 `map[x][y]`를 섞는 실수.
- 회전 방향에서 `(dir+1)%4`와 `(dir+3)%4`를 반대로 쓰는 실수.
- 앞 객체를 먼저 갱신해 뒤 객체의 판정이 바뀌는 순차 갱신 실수.
- 후진은 방향을 바꾸지 않는다는 조건을 놓치는 실수.
- 제출 코드에 중간 상태 출력이 남는 실수.

## 7. 내 코드에서 다시 보기

- [14503.cpp](./14503.cpp): 위치·방향·청소 상태와 회전/후진 종료 조건을 그대로 재현
- [21610.cpp](./21610.cpp): 격자 이동과 여러 단계의 상태 갱신을 턴 단위로 처리
- [10811.cpp](./10811.cpp): 구간 뒤집기 명령을 순서대로 적용하는 작은 시뮬레이션

> [14891.cpp](./14891.cpp)는 디버그 출력이 남아 있어 최소 골격의 대표 코드로 삼지 않았다.
