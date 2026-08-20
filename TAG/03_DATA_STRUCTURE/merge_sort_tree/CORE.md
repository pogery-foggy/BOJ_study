# Merge Sort Tree 기억 복원

## 한 문장 기억

세그먼트 트리의 각 노드에 그 구간의 정렬 배열을 저장해, 구간 안에서 값 기준 개수를 이분 탐색한다.

## 언제 꺼내는가

- 정적 배열에서 `[l, r]` 중 `x`보다 큰/작은 원소 수를 여러 번 물을 때
- 구간의 k번째 수를 값 이분 탐색과 결합해 찾을 때
- 값 갱신이 없고 O(N log N) 메모리를 감당할 수 있을 때

## 핵심 상태/불변식

- `tree[node]`는 정확히 구간 `[s, e]`의 원소를 정렬한 벡터다.
- 빌드 시 두 자식 벡터를 `merge`하므로 전체 O(N log N)이다.
- 완전 포함 노드에서는 `upper_bound/lower_bound` 한 번으로 개수를 센다.

## C++ 최소 구현 골격

```cpp
vector<int> tree[4 * MAX_N];
int a[MAX_N];

void build(int node, int s, int e) {
    if (s == e) { tree[node] = {a[s]}; return; }
    int m = (s + e) / 2;
    build(node * 2, s, m);
    build(node * 2 + 1, m + 1, e);
    auto &L = tree[node * 2], &R = tree[node * 2 + 1];
    tree[node].resize(L.size() + R.size());
    merge(L.begin(), L.end(), R.begin(), R.end(), tree[node].begin());
}

int count_greater(int node, int s, int e, int l, int r, int x) {
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) {
        auto &v = tree[node];
        return v.end() - upper_bound(v.begin(), v.end(), x);
    }
    int m = (s + e) / 2;
    return count_greater(node*2,s,m,l,r,x)
         + count_greater(node*2+1,m+1,e,l,r,x);
}
```

## 빈 화면 구현 순서

1. `vector<int> tree[4N]`와 원본 배열을 선언한다.
2. 리프에 값 하나를 넣고 부모에서 두 벡터를 merge한다.
3. 구간 밖/완전 포함/부분 포함의 세 경우로 query를 쓴다.
4. `>`면 `end-upper_bound`, `>=`면 `end-lower_bound`로 정한다.
5. k번째 수는 후보 값 배열을 정렬하고 `count(<=x) >= k`를 이분 탐색한다.

## 자주 틀리는 지점

- 원본 배열을 값 후보용으로 정렬하기 전에 트리를 먼저 빌드하거나 복사본을 쓴다.
- `lower_bound`와 `upper_bound`의 경계가 문제의 엄격/비엄격 부등호와 맞아야 한다.
- k번째 수의 값 이분 탐색까지 합치면 질의당 O(log²N)이다.
- 동적 갱신 문제라면 이 구조만으로는 비싸므로 다른 자료구조를 검토한다.

## 대표 코드

- [13537.cpp](13537.cpp) — 구간에서 `x`보다 큰 원소 개수
- [7469.cpp](7469.cpp) — 개수 질의와 값 이분 탐색을 결합한 k번째 수
- [14898.cpp](14898.cpp) — 서로 다른 수 질의로 확장한 구현
