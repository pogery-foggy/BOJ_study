# Priority Queue 기억 복원

## 한 문장 기억

지금까지 들어온 후보 중 "다음에 꺼낼 최우선 하나"만 계속 필요할 때 힙을 쓴다.

## 언제 꺼내는가

- 매 단계 최솟값 또는 최댓값 하나를 꺼내고 새 값을 넣을 때
- 종료 시간이 가장 빠른 강의실, 비용이 가장 작은 작업 등 greedy의 후보 관리가 필요할 때
- 모든 원소의 정렬 순서는 필요 없고 최우선 원소만 필요할 때

## 핵심 상태/불변식

- `top()`은 현재 컨테이너 전체의 최우선 원소다.
- 최소 힙은 `priority_queue<T, vector<T>, greater<T>>`다.
- 구간 스케줄링에서는 힙에 "현재 사용 중인 자원의 종료 시각"만 남긴다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [1927.cpp](1927.cpp)의 전역 최소 힙, `init()`/`solve()` 분리, `user_in`이라는 입력 변수와 `if (!user_in)` 명령 분기를 그대로 보존했다.

```cpp
using namespace std;

priority_queue<long long, vector<long long>, greater<long long>> pq;
int N;

void init() { cin >> N; }

void solve() {
    long long user_in;
    for (int i = 0; i < N; i++) {
        cin >> user_in;
        if (!user_in) {
            if (pq.empty()) {
                cout << "0\n";
            } else {
                cout << pq.top() << "\n";
                pq.pop();
            }
        } else {
            pq.push(user_in);
        }
    }
}
```

강의실·작업 스케줄 문제도 같은 `pq.top()` 확인 뒤 `pop()`/`push()` 순서를 쓰되, 실제 코드에 없던 구조적 바인딩은 골격에 넣지 않는다.

## 빈 화면 구현 순서

1. 우선순위 기준이 최소인지 최대인지 문장으로 적는다.
2. 힙 원소에 값만 넣을지 `{비용, 정점}` 같은 쌍을 넣을지 정한다.
3. 매 단계 `top → pop → 상태 반영 → push` 순서를 쓴다.
4. stale 원소가 생기는 문제면 `while(top이 현재 상태와 다름) pop`을 둔다.
5. 빈 힙 입력/출력을 따로 검사한다.

## 자주 틀리는 지점

- 기본 `priority_queue`는 최대 힙이다.
- `top()`을 읽기 전에 `empty()`를 확인한다.
- 강의실 문제에서는 한 강의를 처리할 때 재사용 가능한 방 하나만 pop하고 종료 시각 하나를 push한다.
- 쌍은 첫 원소부터 사전순 비교되므로 필드 순서를 우선순위에 맞춘다.

## 대표 코드

- [1927.cpp](1927.cpp) — `greater`를 사용한 최소 힙 기본형
- [11000.cpp](11000.cpp) — 종료 시각 최소 힙으로 필요한 자원 수를 세는 패턴
- [15903.cpp](15903.cpp) — 가장 작은 두 값을 반복해서 합치는 greedy
