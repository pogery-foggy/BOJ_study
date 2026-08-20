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

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [1620.cpp](1620.cpp)의 전역 문자열 배열 `answer`, `map<string, int> dogam`, `init()`에서 양방향 표를 동시에 만들고 `solve()`에서 첫 글자로 숫자 질의를 구별하는 구성을 그대로 축약했다.

```cpp
#define MAX_N 100001
using namespace std;

int N, M;
string answer[MAX_N];
map<string, int> dogam;

void init() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> answer[i];
        dogam.insert({answer[i], i});
    }
}

void solve() {
    string user_in;
    for (int i = 0; i < M; i++) {
        cin >> user_in;
        if ('0' <= user_in[0] && user_in[0] <= '9')
            cout << answer[stoi(user_in)] << "\n";
        else
            cout << dogam[user_in] << "\n";
    }
}
```

기존 골격의 `unordered_map`·`vector`는 이 대표 풀이의 선택이 아니므로 `map`·고정 배열로 되돌렸다. 양끝 삭제가 핵심인 문제는 [7662.cpp](7662.cpp)의 `multiset` 사용을 따로 참고한다.

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
