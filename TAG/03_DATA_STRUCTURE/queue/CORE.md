# Queue 기억 복원

## 한 문장 기억

먼저 들어온 사건을 먼저 처리해야 시간·도착 순서가 흐트러지지 않을 때 FIFO 큐를 쓴다.

## 언제 꺼내는가

- BFS처럼 거리/단계가 작은 상태부터 처리할 때
- 도착 순서를 보존하는 대기열 시뮬레이션일 때
- 원형으로 앞사람을 처리하고 뒤로 보내는 과정일 때

## 핵심 상태/불변식

- 아직 처리하지 않은 원소는 입력 또는 발견 순서 그대로 큐에 있다.
- 시뮬레이션에서 큐의 `front()`는 그쪽에서 가장 먼저 도착한 사람이다.
- 답을 원래 입력 순서로 내야 하면 큐에는 값 대신 입력 인덱스를 넣는다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [2065.cpp](2065.cpp)의 `queue<int> q[2]`, 입력 순서를 보존하는 `vector<pair<int, string>> user_in`, 전역 `isleft`, `time`, `answer`와 명시적인 정원 반복문을 축약했다.

```cpp
using namespace std;

int M, t, N, time;
vector<pair<int, string>> user_in;
queue<int> q[2];
bool isleft, flag;
int answer[10001];

void init() {
    cin >> M >> t >> N;
    for (int i = 0; i < N; i++) {
        int a;
        string b;
        cin >> a >> b;
        user_in.push_back(make_pair(a, b));
        if (b == "left") q[0].push(i);
        else q[1].push(i);
    }
}

void solve() {
    while (1) {
        if (q[0].empty() && q[1].empty())
            break;
        flag = false;

        if (!q[isleft].empty()) {
            for (int i = M; i > 0; i--) {
                if (!q[isleft].empty()
                    && user_in[q[isleft].front()].first <= time) {
                    answer[q[isleft].front()] = time + t;
                    q[isleft].pop();
                    flag = true;
                } else {
                    break;
                }
            }

            if (flag) {
                time += t;
                isleft = !isleft;
            } else if (!q[!isleft].empty()) {
                if (user_in[q[isleft].front()].first
                    <= user_in[q[!isleft].front()].first) {
                    time += max(0, user_in[q[isleft].front()].first - time);
                } else {
                    time += t + max(0, user_in[q[!isleft].front()].first - time);
                    isleft = !isleft;
                }
            } else {
                time += max(0, user_in[q[isleft].front()].first - time);
            }
        } else if (!q[!isleft].empty()) {
            time += t + max(0, user_in[q[!isleft].front()].first - time);
            isleft = !isleft;
        }
    }
}
```

[2065.cpp](2065.cpp)의 `flag`와 중첩 분기를 그대로 남겼다. 현재 편 큐가 비었는지는 바깥 `if`, 반대편 큐는 각각의 `!empty()` 조건에서 먼저 검사하므로 근거 없는 별도 “안전 교정”은 넣지 않았다.

## 빈 화면 구현 순서

1. 큐 원소가 상태인지 입력 인덱스인지 정한다.
2. 초기 원소를 발견/도착 순서로 넣는다.
3. 루프 첫 줄을 `front`, 다음 줄을 `pop`으로 고정한다.
4. 새 상태는 조건을 통과하고 아직 방문하지 않았을 때만 넣는다.
5. 아무 일도 못 한 시뮬레이션에서는 시간을 1씩 늘리지 말고 다음 사건 시각으로 점프한다.

## 자주 틀리는 지점

- 빈 큐의 `front()`를 읽지 않는다.
- 처리한 원소를 조건 없이 다시 넣으면 무한 루프가 된다.
- 여러 큐 중 다음 도착을 비교할 때 비어 있는 쪽은 먼저 제외한다.
- 이 폴더의 [11866.cpp](11866.cpp)는 이름과 달리 순서 통계 세그먼트 트리 풀이이므로 큐 복습 대표로 삼지 않는다.

## 대표 코드

- [2065.cpp](2065.cpp) — 좌우 도착 순서를 별도 큐에 보존한 나룻배 시뮬레이션
- [11866.cpp](11866.cpp) — 같은 요세푸스 문제를 큐가 아닌 순서 통계 트리로 푼 비교 자료
