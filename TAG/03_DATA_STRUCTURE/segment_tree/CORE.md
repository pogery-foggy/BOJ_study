# Segment Tree 기억 복원

## 한 문장 기억

구간의 요약값을 두 자식의 결합으로 유지해, 한 점/구간 변경과 구간 질의를 O(log N)에 처리한다.

## 언제 꺼내는가

- 배열이 바뀌면서 구간 합·최솟값·최댓값·곱을 반복 질의할 때
- k번째 활성 원소처럼 왼쪽 자식의 개수를 보고 내려갈 때
- 여러 필드의 결합법이 정의되는 최대 부분합 같은 질의일 때

## 핵심 상태/불변식

- `tree[node] = merge(tree[node*2], tree[node*2+1])`가 항상 성립한다.
- query의 구간 밖 반환값은 merge의 항등원이어야 한다.
- lazy 값은 "이 노드 구간에는 반영됐지만 자식에는 아직 전달하지 않은 연산"이다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [2042.cpp](2042.cpp)의 전역 `tree`, `arr`, 리프 노드를 기억하는 `arr_index`, `(s, e, node)` 순서의 `init_tree`·`sum`, 리프에서 루트까지 올라가는 반복형 `update`를 그대로 축약했다.

```cpp
#define MAX_N 1000000
typedef long long ll;
using namespace std;

int N, arr_index[MAX_N + 1];
ll tree[4 * MAX_N], arr[MAX_N];

ll init_tree(int s, int e, int node) {
    if (s == e) {
        arr_index[s + 1] = node;
        return tree[node] = arr[s];
    }
    int mid = (s + e) >> 1;
    return tree[node] = init_tree(s, mid, node << 1)
                      + init_tree(mid + 1, e, node << 1 | 1);
}

void update(int idx, ll change) {
    int fnd = arr_index[idx];
    tree[fnd] = change;
    fnd /= 2;
    while (fnd > 0) {
        tree[fnd] = tree[fnd << 1] + tree[fnd << 1 | 1];
        fnd /= 2;
    }
}

ll sum(int s, int e, int l, int r, int node) {
    if (l > e || r < s)
        return 0;
    if (l <= s && e <= r)
        return tree[node];
    int mid = (s + e) / 2;
    return sum(s, mid, l, r, node << 1)
         + sum(mid + 1, e, l, r, node << 1 | 1);
}
```

구간 갱신 문제에서는 [10999.cpp](10999.cpp)처럼 같은 전역 배열·재귀 인자 순서를 유지한 채 `lazy`와 전파 함수를 추가한다.

## 빈 화면 구현 순서

1. 노드가 저장할 요약값과 `merge`, 항등원을 먼저 적는다.
2. 리프와 부모 merge로 build한다.
3. query를 구간 밖/완전 포함/부분 포함으로 나눈다.
4. point update를 쓰고 부모를 다시 merge한다.
5. 구간 update가 필요할 때만 `apply`, `push`, lazy를 추가한다.

## 자주 틀리는 지점

- 입력의 1-based 인덱스를 내부 0-based와 섞지 않는다.
- 최솟값 질의의 구간 밖 값은 0이 아니라 `INF`다.
- lazy를 내려보내기 전에 현재 노드에 두 번 반영하지 않는다.
- 최대 부분합 노드는 `sum/lmx/rmx/mx` 네 필드와 올바른 항등원이 모두 필요하다.

## 대표 코드

- [2042.cpp](2042.cpp) — 점 대입과 구간 합 기본형
- [10999.cpp](10999.cpp) — 구간 덧셈 lazy propagation
- [13557.cpp](13557.cpp) — `sum/lmx/rmx/mx`를 merge하는 최대 부분합 노드
- [2243.cpp](2243.cpp) — 왼쪽 개수를 보며 k번째 원소를 찾는 순서 통계
