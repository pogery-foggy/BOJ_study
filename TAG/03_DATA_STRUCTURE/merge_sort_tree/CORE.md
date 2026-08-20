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

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [13537.cpp](13537.cpp)의 `tree[MAX_N * 4]`와 `arr`, `(s, e, node)` 순서의 재귀 함수, `node << 1` 자식 표기, 노드 벡터를 참조로 받은 뒤 `merge`하는 구성을 유지했다.

```cpp
#define MAX_N 100000
using namespace std;

vector<int> tree[MAX_N * 4];
int arr[MAX_N];
int N;

void init_tree(int s, int e, int node) {
    if (s == e) {
        tree[node].push_back(arr[s]);
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    auto &l = tree[node << 1];
    auto &r = tree[node << 1 | 1];
    tree[node].resize(int(l.size() + r.size()));
    merge(l.begin(), l.end(), r.begin(), r.end(), tree[node].begin());
}

int query(int s, int e, int l, int r, int x, int node) {
    if (r < s || e < l)
        return 0;
    if (l <= s && e <= r) {
        auto &cur = tree[node];
        return cur.end() - upper_bound(cur.begin(), cur.end(), x);
    }
    int mid = (s + e) >> 1;
    return query(s, mid, l, r, x, node << 1)
         + query(mid + 1, e, l, r, x, node << 1 | 1);
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
