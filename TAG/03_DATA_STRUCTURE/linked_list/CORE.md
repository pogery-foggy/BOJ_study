# Linked List 기억 복원

## 한 문장 기억

커서 주변의 두 연결만 다시 잇으면 중간 삽입·삭제가 위치 이동 없이 끝난다.

## 언제 꺼내는가

- 커서가 좌우로 움직이며 바로 옆 문자를 삽입하거나 삭제할 때
- 원소의 주소가 유지되어야 하고 중간 수정이 잦을 때
- 단, 단순 편집기라면 `std::list` 반복자나 왼쪽/오른쪽 두 스택도 먼저 고려한다.

## 핵심 상태/불변식

- `head`와 `tail` 더미 노드가 있어 실제 첫/끝 원소도 같은 코드로 처리한다.
- 사용자 코드의 `current`는 커서 바로 왼쪽 노드를 뜻한다.
- 항상 `x->next->prev == x`, `x->prev->next == x`가 성립해야 한다.

## C++ 최소 구현 골격

```cpp
struct Node {
    char value;
    Node *prev = nullptr, *next = nullptr;
};

Node head, tail;
Node* cursor = &head; // 커서 왼쪽 문자

void init_list() {
    head.next = &tail;
    tail.prev = &head;
}

void insert_after(Node* cur, char c) {
    Node* x = new Node{c, cur, cur->next};
    cur->next->prev = x;
    cur->next = x;
    cursor = x;
}

void erase_cursor() {
    if (cursor == &head) return;
    Node* victim = cursor;
    cursor = victim->prev;
    cursor->next = victim->next;
    victim->next->prev = cursor;
    delete victim;
}
```

## 빈 화면 구현 순서

1. 더미 `head`, `tail`을 서로 연결한다.
2. 커서의 의미를 "왼쪽 노드"로 한 줄 적는다.
3. 삽입 시 새 노드의 두 포인터를 먼저 채운 뒤 이웃 포인터를 바꾼다.
4. 삭제 시 이전 노드를 저장하고 네 연결을 다시 잇는다.
5. 출력은 `head.next`부터 `tail` 직전까지 순회한다.

## 자주 틀리는 지점

- 삭제한 포인터를 다시 따라가지 않는다. 다음 커서를 먼저 저장한다.
- 빈 문자열 출력에서 `tail->data`를 출력하지 않는다.
- 왼쪽 끝/오른쪽 끝 이동 조건을 더미 노드 기준으로 검사한다.
- 직접 `new`했다면 장기 실행에서는 `delete` 또는 노드 풀을 고려한다.

## 대표 코드

- [1406.cpp](1406.cpp) — 양방향 노드와 두 더미 노드로 만든 편집기
