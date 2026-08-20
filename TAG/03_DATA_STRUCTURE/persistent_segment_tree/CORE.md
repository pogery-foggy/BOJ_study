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

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [16978.cpp](16978.cpp)의 `typedef long long ll`, 인덱스로 자식을 저장하는 `Node`, 전역 노드 풀과 `node_cnt`, 새 루트를 반환하는 재귀 `update(s, e, node, idx, v)` 구성을 그대로 축약했다.

```cpp
#define MAX_N 100001
#define MAX_M 100001
#define MAX_NODE 2200000
typedef long long ll;

struct Node{
    int l, r;
    ll val;
    Node(): l(-1), r(-1), val(0){}
};

Node tree[MAX_NODE];
int node_cnt, root_cnt;
int root[MAX_M + 1];
ll arr[MAX_N];

int new_node(int l, int r, ll val){
    int node = node_cnt++;
    tree[node].l = l;
    tree[node].r = r;
    tree[node].val = val;
    return node;
}

int init_tree(int s, int e){
    if(s == e)
        return new_node(-1, -1, arr[s]);
    int mid = (s + e) >> 1;
    int l = init_tree(s, mid);
    int r = init_tree(mid + 1, e);
    return new_node(l, r, tree[l].val + tree[r].val);
}

int update(int s, int e, int node, int idx, ll v){
    int next = new_node(tree[node].l, tree[node].r, tree[node].val);

    if(s == e){
        tree[next].val = v;
        return next;
    }
    int mid = (s + e) >> 1;
    if(idx <= mid)
        tree[next].l = update(s, mid, tree[node].l, idx, v);
    else
        tree[next].r = update(mid + 1, e, tree[node].r, idx, v);

    int L = tree[next].l;
    int R = tree[next].r;
    tree[next].val = tree[L].val + tree[R].val;
    return next;
}

ll query(int s, int e, int l, int r, int node){
    if(r < s || e < l) return 0;
    if(l <= s && e <= r) return tree[node].val;
    int mid = (s + e) >> 1;
    return query(s, mid, l, r, tree[node].l)
         + query(mid + 1, e, l, r, tree[node].r);
}
```

새 버전은 실제 코드처럼 `root[root_cnt] = update(..., root[root_cnt-1], ...)`로 받고 `root_cnt`를 증가시킨다.

## 빈 화면 구현 순서

1. 노드 풀 크기를 `초기 노드 + 갱신 수 × (logN + 여유)`로 계산한다.
2. 초기 트리와 `root[0]`을 만든다.
3. 실제 코드처럼 이전 노드의 두 자식과 값을 복사하는 `new_node` 호출을 update 첫 줄에 둔다.
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
