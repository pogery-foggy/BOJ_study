# Splay Tree 기억 복원

## 한 문장 기억

접근한 노드를 회전으로 루트까지 끌어올리고, 서브트리 크기를 이용해 배열의 k번째 위치와 연속 구간을 트리로 다룬다.

## 언제 꺼내는가

- 수열 중간 구간을 잘라 이동·뒤집기·갱신해야 할 때
- 인덱스가 계속 변해도 k번째 원소 접근과 구간 집계가 필요할 때
- implicit key balanced tree가 필요하고 splay 구현을 사용할 수 있을 때

## 핵심 상태/불변식

- 중위 순회 순서가 곧 수열 순서다.
- `cnt = 1 + size(left) + size(right)`는 모든 회전 뒤 즉시 갱신한다.
- 양끝 더미를 두면 실제 `[l, r]`은 `kth(l-1)`을 루트로, `kth(r+1)`을 그 오른쪽 자식으로 만든 뒤 `right->left`에 모인다.
- lazy가 있다면 회전/탐색 전에 루트부터 대상까지 `push`한다.

## C++ 최소 구현 골격

```cpp
struct Node {
    Node *l=nullptr, *r=nullptr, *p=nullptr;
    int value=0, cnt=1;
};
Node* root;
int sz(Node* x) { return x ? x->cnt : 0; }
void pull(Node* x) { if (x) x->cnt = 1 + sz(x->l) + sz(x->r); }

void rotate(Node* x) {
    Node *p=x->p, *g=p->p, *b;
    if (x == p->l) b=x->r, x->r=p, p->l=b;
    else b=x->l, x->l=p, p->r=b;
    if (b) b->p=p;
    x->p=g; p->p=x;
    if (!g) root=x;
    else (g->l==p ? g->l : g->r)=x;
    pull(p); pull(x);
}

void splay(Node* x, Node* goal=nullptr) {
    while (x->p != goal) {
        Node *p=x->p, *g=p->p;
        if (g == goal) rotate(x);
        else if ((x==p->l) == (p==g->l)) rotate(p), rotate(x);
        else rotate(x), rotate(x);
    }
    if (!goal) root=x;
}
```

`kth(k)`는 왼쪽 크기와 k를 비교해 내려간 뒤 찾은 노드를 splay한다. `gather(l,r)`는 오른쪽 경계와 왼쪽 경계를 차례로 splay해 가운데 서브트리를 노출한다.

## 빈 화면 구현 순서

1. `Node`, `size`, `pull`, 필요 lazy의 `push`를 만든다.
2. 포인터 여섯 곳을 다시 잇는 `rotate`를 그림과 함께 구현한다.
3. zig / zig-zig / zig-zag의 `splay`를 쓴다.
4. 서브트리 크기로 `kth`를 구현한다.
5. 양끝 더미를 포함해 초기 트리를 만들고 `gather(l,r)`를 구현한다.
6. 그 뒤에만 cut/insert/reverse 같은 문제 연산을 붙인다.

## 자주 틀리는 지점

- 회전 전 lazy를 위에서 아래 순서로 push하지 않으면 좌우 의미가 깨진다.
- `rotate` 뒤에는 아래로 내려간 부모를 먼저 pull하고 x를 pull한다.
- 실제 위치와 더미를 포함한 k번째 인덱스가 한 칸씩 다르다.
- 잘라낸 서브트리의 `p=nullptr`, 붙인 루트의 `p=새 부모`를 모두 설정한다.
- `19589.cpp`는 빈 파일이므로 구현 복습 자료로 사용하지 않는다.

## 대표 코드

- [16586.cpp](16586.cpp) — 더미·kth·gather·cut·insert가 모두 있는 implicit splay 기본판
- [23705.cpp](23705.cpp) — 서브트리에 합과 prefix 최소 정보를 얹은 구현
- [29162.cpp](29162.cpp) — 수열 구간 연산과 lazy를 포함한 응용
