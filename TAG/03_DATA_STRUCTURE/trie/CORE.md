# Trie 기억 복원

## 한 문장 기억

키를 앞자리부터 한 단계씩 내려가며 공유하고, XOR 문제에서는 최상위 비트부터 반대 가지를 탐욕적으로 고른다.

## 언제 꺼내는가

- 문자열 접두사 검색 또는 사전 집합을 다룰 때
- 수 집합에서 최대/최소 XOR 상대를 빠르게 찾을 때
- 삽입·삭제·질의가 섞이고 키 길이가 고정되어 있을 때

## 핵심 상태/불변식

- 사용자 코드의 자식 `l/r`은 각각 다음 비트가 `0/1`인 경로다. 다른 구현에서는 같은 두 칸을 `next[0/1]`로 표현하기도 한다.
- `cnt`는 그 노드를 통과하는 현재 원소 수라서 삭제 후에도 가지가 유효한지 판단한다.
- 최대 XOR은 높은 비트가 답을 지배하므로 매 비트에서 `bit ^ 1` 가지를 먼저 고른다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [13505.cpp](13505.cpp)의 왼쪽/오른쪽 자식을 `l`, `r`로 둔 `Node`, 고정 노드 배열을 감싼 `Trie`, `Trie` 안의 `bits[30]`, `cur`을 직접 옮기는 `insert`·`query` 구성을 보존했다.

```cpp
#define MAX_NODE 6006000

struct Node {
    int l, r;
    int cnt, terminate;
    Node() : l(-1), r(-1), cnt(0), terminate(-1) {}
};

struct Trie {
    Node node[MAX_NODE];
    int root;
    queue<int> q;
    int bits[30];

    Trie() {
        for (int i = 0; i < MAX_NODE; i++)
            q.push(i);
        root = new_node();
    }

    int new_node() {
        int ret = q.front();
        q.pop();
        return ret;
    }

    void insert(int x) {
        int cur = root, val = x;
        for (int i = 29; i >= 0; i--) {
            bits[i] = x & 1;
            x >>= 1;
        }
        for (int i = 0; i < 30; i++) {
            if (bits[i]) {
                if (node[cur].r == -1)
                    node[cur].r = new_node();
                cur = node[cur].r;
            } else {
                if (node[cur].l == -1)
                    node[cur].l = new_node();
                cur = node[cur].l;
            }
            node[cur].cnt++;
            if (i == 29) node[cur].terminate = val;
        }
    }

    int query(int x) {
        int cur = root, val = x;
        for (int i = 29; i >= 0; i--) {
            bits[i] = x & 1;
            x >>= 1;
        }
        for (int i = 0; i < 30; i++) {
            if (bits[i]) {
                if (node[cur].l != -1) cur = node[cur].l;
                else cur = node[cur].r;
            } else {
                if (node[cur].r != -1) cur = node[cur].r;
                else cur = node[cur].l;
            }
        }
        return val ^ node[cur].terminate;
    }
};
```

실제 풀이처럼 큐에서 노드 번호를 할당한다. 원본 `query()`의 반복 조건 `i <= 30`은 유효한 단말에서 먼저 반환한다는 전제에 기대며 `bits[30]` 접근 위험이 있으므로, 골격에서는 같은 탐색 구조를 유지하되 정확히 30번만 도는 `i < 30`으로 교정했다. 삭제까지 필요한 [16903.cpp](16903.cpp)에서는 `cnt`가 0이 된 노드를 다시 쓸 수 있도록 초기화한 뒤 `q.push(next)`로 번호를 반환해야 한다.

## 빈 화면 구현 순서

1. 최대 값으로 최상위 비트 `B`를 정한다.
2. 노드에 자식과 통과 개수 `cnt`를 둔다.
3. 삽입은 `B → 0`으로 내려가며 자식을 만들고 개수를 올린다.
4. 삭제는 같은 경로의 개수만 내린다.
5. 질의는 반대 비트 가지의 `cnt > 0`을 먼저 검사한다.

## 자주 틀리는 지점

- 집합이 비지 않도록 동적 질의에서는 보통 0을 먼저 삽입한다.
- 삭제 때 노드를 물리적으로 끊지 않아도 `cnt`만 정확하면 된다.
- `for (b = B; b >= 0; --b)`의 횟수와 배열 크기를 맞춘다.
- `1 << 31`이 필요하면 부호 문제를 피하려 `1ULL << b`를 쓴다.

## 대표 코드

- [13505.cpp](13505.cpp) — 배열 기반 이진 트라이와 최대 XOR 선택
- [16903.cpp](16903.cpp) — 삽입·삭제·최대 XOR이 섞인 동적 트라이
- [13504.cpp](13504.cpp) — 누적 XOR과 트라이를 결합한 응용
