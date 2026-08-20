# Set / Map 기억 복원

## 한 문장 기억

키의 존재 여부·빈도·대응 값을 빠르게 찾고, 정렬까지 필요하면 트리 기반 `set/map`을 고른다.

## 언제 꺼내는가

- 문자열에서 번호, 번호에서 문자열을 서로 조회할 때
- 중복 제거, 빈도 계산, 교집합을 구할 때
- 현재 최솟값과 최댓값을 모두 삭제해야 할 때

## 핵심 상태/불변식

- `map[key] = value`는 키마다 값 하나, `set`은 키 자체 하나를 보관한다.
- `multiset`은 같은 값의 개수까지 보존하며 `erase(iterator)`는 딱 하나만 지운다.
- 정렬이 필요 없으면 평균 O(1) `unordered_map/set`, 순서·양끝이 필요하면 O(log N) `map/set`이다.

## C++ 최소 구현 골격

```cpp
vector<string> by_id(n + 1);
unordered_map<string, int> by_name;

for (int i = 1; i <= n; ++i) {
    cin >> by_id[i];
    by_name[by_id[i]] = i;
}

multiset<int> ms;
ms.insert(x);
if (!ms.empty()) ms.erase(ms.begin());       // 최솟값 하나
if (!ms.empty()) ms.erase(prev(ms.end()));   // 최댓값 하나
```

## 빈 화면 구현 순서

1. 필요한 연산을 `존재/값 조회/빈도/정렬/양끝`으로 적는다.
2. 그 연산에 맞춰 `unordered_*`, `map/set`, `multiset` 중 하나를 고른다.
3. 입력과 동시에 자료구조에 넣고, 원래 순서가 필요하면 별도 배열도 둔다.
4. 조회에서 없는 키를 삽입하면 안 되면 `find`를 쓴다.
5. 삭제가 "값 전부"인지 "한 개"인지 확인한다.

## 자주 틀리는 지점

- `ms.erase(value)`는 같은 값을 모두 지우지만 `ms.erase(ms.find(value))`는 하나만 지운다.
- `map[key]` 조회는 없는 키를 기본값으로 새로 만든다.
- `--ms.end()`는 비어 있지 않을 때만 가능하고 `prev(ms.end())`가 읽기 쉽다.
- 문자열이 숫자인지 판단할 때 빈 문자열과 부호 여부를 확인한다.

## 대표 코드

- [1620.cpp](1620.cpp) — 배열과 문자열→번호 맵을 함께 둔 양방향 조회
- [7662.cpp](7662.cpp) — `multiset`의 양끝을 이용한 이중 우선순위 큐
- [4358.cpp](4358.cpp) — 정렬된 키별 빈도 출력
