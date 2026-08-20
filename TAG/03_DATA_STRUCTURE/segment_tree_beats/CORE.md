# Segment Tree Beats 기억 복원

## 한 문장 기억

최댓값과 두 번째 최댓값을 함께 저장해 `chmin(x)`가 최대 원소들만 바꾸는 구간이면 더 내려가지 않고 친다.

## 언제 꺼내는가

- 구간 `a[i] = min(a[i], x)` 또는 `max` 연산과 합/최댓값 질의가 섞일 때
- 일반 lazy로는 연산을 한 값으로 합성하기 어렵지만 노드 상태로 변화 대상을 제한할 수 있을 때
- "이번 연산으로 바뀌는 값의 종류가 하나뿐"인지를 빠르게 판정할 수 있을 때

## 핵심 상태/불변식

- chmin형 노드는 `sum`, 최대 `mx1`, 두 번째 최대 `mx2`, 최대 개수 `cnt`를 가진다.
- `mx1 <= x`면 아무것도 변하지 않는다.
- `mx2 < x < mx1`이면 최대인 원소만 x가 되므로 노드에서 즉시 처리한다.
- push는 자식의 `mx1`이 부모 `mx1`보다 크지 않도록 동기화한다.

## C++ 최소 구현 골격

```cpp
struct Node { long long sum, mx1, mx2; int cnt; };

void apply_chmin(int node, long long x) {
    if (tree[node].mx1 <= x) return;
    tree[node].sum -= (tree[node].mx1 - x) * tree[node].cnt;
    tree[node].mx1 = x;
}

void push(int node) {
    apply_chmin(node * 2, tree[node].mx1);
    apply_chmin(node * 2 + 1, tree[node].mx1);
}

void chmin(int node, int s, int e, int l, int r, long long x) {
    if (e < l || r < s || tree[node].mx1 <= x) return;
    if (l <= s && e <= r && tree[node].mx2 < x) {
        apply_chmin(node, x);
        return;
    }
    push(node);
    int m = (s + e) / 2;
    chmin(node*2,s,m,l,r,x);
    chmin(node*2+1,m+1,e,l,r,x);
    tree[node] = merge_node(tree[node*2], tree[node*2+1]);
}
```

## 빈 화면 구현 순서

1. 연산이 chmin인지 chmax인지 정하고 극값 1·2등과 개수를 정의한다.
2. 리프와 `merge_node`를 먼저 완성한다.
3. 한 노드에 연산을 적용하는 `apply`를 쓴다.
4. 부모 제한을 자식에 전달하는 `push`를 쓴다.
5. 무변화/노드 즉시 처리/재귀의 세 조건으로 update를 쓴다.

## 자주 틀리는 지점

- 두 번째 최댓값의 초기값은 충분히 작은 `-INF`다.
- `mx2 < x`는 엄격 부등호다. `x == mx2`면 여러 값 계층이 합쳐져 내려가야 한다.
- 합 보정은 `(옛 mx1 - 새 mx1) * cnt`다.
- 일반 세그먼트 트리보다 상태 조합과 push 순서가 민감하므로 작은 배열 brute force와 대조한다.

## 대표 코드

- [17474.cpp](17474.cpp) — `chmin + max + sum`의 표준 beats 구현
- [17476.cpp](17476.cpp) — min/max가 같은 구간을 한 번에 덮는 sqrt 갱신 응용
- [17477.cpp](17477.cpp) — 여러 제한 연산을 결합한 확장형
