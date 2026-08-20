# Persistent Segment Tree 기억 복원

## 한 문장 기억

갱신 경로의 O(log N) 노드만 복사하고 나머지 자식은 공유해, 과거 버전의 루트를 모두 보존한다.

## 언제 꺼내는가

- k번째 갱신 이후의 배열을 다시 질의할 때
- 접두사 버전 `root[r] - root[l-1]`로 구간 빈도·k번째 수를 찾을 때
- 롤백보다 여러 과거 버전에 임의 접근이 필요할 때

## 핵심 상태/불변식

- `root[k]`는 k번째 버전 전체를 대표한다.
- update는 기존 노드를 바꾸지 않고 방문한 노드만 복제해 새 루트를 반환한다.
- 방문하지 않은 반대쪽 자식 인덱스는 이전 버전과 공유한다.

## C++ 최소 구현 골격

```cpp
struct Node { int l = 0, r = 0; long long sum = 0; };
Node tr[MAX_NODE];
int roots[MAX_Q], nodes = 0;

int clone_node(int from) {
    tr[++nodes] = tr[from];
    return nodes;
}

int update(int prev, int s, int e, int idx, long long value) {
    int cur = clone_node(prev);
    if (s == e) { tr[cur].sum = value; return cur; }
    int m = (s + e) / 2;
    if (idx <= m) tr[cur].l = update(tr[prev].l, s, m, idx, value);
    else tr[cur].r = update(tr[prev].r, m + 1, e, idx, value);
    tr[cur].sum = tr[tr[cur].l].sum + tr[tr[cur].r].sum;
    return cur;
}

long long query(int cur, int s, int e, int l, int r) {
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tr[cur].sum;
    int m = (s + e) / 2;
    return query(tr[cur].l,s,m,l,r) + query(tr[cur].r,m+1,e,l,r);
}
```

## 빈 화면 구현 순서

1. 노드 풀 크기를 `초기 노드 + 갱신 수 × (logN + 여유)`로 계산한다.
2. 초기 트리와 `root[0]`을 만든다.
3. 이전 노드를 복사하는 `clone_node`를 만든다.
4. update가 새 노드 번호를 반환하도록 쓴다.
5. 버전별 루트를 저장하고 질의에 원하는 루트를 넘긴다.

## 자주 틀리는 지점

- 전역 `nodes`와 버전 번호를 섞지 않는다.
- 자식 0번을 빈 노드로 쓸 때 `tr[0]`이 0으로 초기화되어야 한다.
- 노드 풀 상한이 부족하면 런타임 오류 대신 메모리 오염이 날 수 있다.
- 두 접두사 차로 질의할 때 개수는 항상 `rightRoot - leftRoot` 순서다.

## 대표 코드

- [16978.cpp](16978.cpp) — 경로 복사와 버전별 구간 합의 가장 직접적인 구현
- [13538.cpp](13538.cpp) — 접두사 버전 차로 XOR·개수·k번째 수를 처리한 응용
- [11012.cpp](11012.cpp) — 스위핑과 영속 세그먼트 트리 결합
