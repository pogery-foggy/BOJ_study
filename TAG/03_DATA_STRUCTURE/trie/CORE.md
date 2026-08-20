# Trie 기억 복원

## 한 문장 기억

키를 앞자리부터 한 단계씩 내려가며 공유하고, XOR 문제에서는 최상위 비트부터 반대 가지를 탐욕적으로 고른다.

## 언제 꺼내는가

- 문자열 접두사 검색 또는 사전 집합을 다룰 때
- 수 집합에서 최대/최소 XOR 상대를 빠르게 찾을 때
- 삽입·삭제·질의가 섞이고 키 길이가 고정되어 있을 때

## 핵심 상태/불변식

- 노드의 자식 `next[0/1]`은 다음 비트가 0/1인 경로다.
- `cnt`는 그 노드를 통과하는 현재 원소 수라서 삭제 후에도 가지가 유효한지 판단한다.
- 최대 XOR은 높은 비트가 답을 지배하므로 매 비트에서 `bit ^ 1` 가지를 먼저 고른다.

## C++ 최소 구현 골격

```cpp
struct Node {
    int next[2] = {-1, -1};
    int cnt = 0;
};
vector<Node> tr(1);

void insert(int x, int delta) {
    int cur = 0;
    for (int b = 29; b >= 0; --b) {
        int v = (x >> b) & 1;
        if (tr[cur].next[v] == -1) {
            tr[cur].next[v] = tr.size();
            tr.emplace_back();
        }
        cur = tr[cur].next[v];
        tr[cur].cnt += delta;
    }
}

int max_xor(int x) {
    int cur = 0, ans = 0;
    for (int b = 29; b >= 0; --b) {
        int v = (x >> b) & 1, want = v ^ 1;
        int nx = tr[cur].next[want];
        if (nx != -1 && tr[nx].cnt > 0) ans |= 1 << b, cur = nx;
        else cur = tr[cur].next[v];
    }
    return ans;
}
```

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
