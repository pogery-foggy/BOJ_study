# Mo's Algorithm 기억 복원

## 한 문장 기억

오프라인 구간 질의를 가까운 순서로 재배열해, 현재 구간의 양끝을 한 칸씩 옮기며 답을 재사용한다.

## 언제 꺼내는가

- 배열 갱신이 없고 구간 질의를 모두 미리 받을 수 있을 때
- 원소 하나를 구간에 더하거나 뺄 때 답 상태를 빠르게 고칠 수 있을 때
- 일반적인 세그먼트 트리 merge로 답을 만들기 어려울 때

## 핵심 상태/불변식

- 항상 자료구조가 현재 구간 `[curL, curR]`의 정보만 정확히 나타낸다.
- 질의는 `L / block` 우선, 그다음 `R` 순으로 정렬한다.
- `add/remove`는 정확히 서로 역연산이어야 하며 답은 원래 질의 인덱스에 저장한다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [13546.cpp](13546.cpp)의 전역 `sqrtN`, 멤버가 `idx, s, e`인 `Query`, 구조체 내부 `operator <`, 네 방향을 별도 함수로 나눈 포인터 이동을 그대로 축약했다. 비어 있는 `21064.cpp`는 근거로 사용하지 않았다.

```cpp
#define MAX_N 100001
#define MAX_K 100001
#define MAX_B 400

int sqrtN;
int bucket_cnt[MAX_B];
int dist_cnt[MAX_N];
int answer[MAX_N];

struct Query{
    int idx, s, e;
    bool operator <(const Query &x) const {
        if (s/sqrtN != x.s/sqrtN)
            return s/sqrtN < x.s/sqrtN;
        return e < x.e;
    }
};

int N, K, Q;
vector<Query> query;
vector<int> v;
deque<int> pos[MAX_K];

int get_answer(){
    for(int b = N / sqrtN; b >= 0; b--){
        if(bucket_cnt[b] == 0) continue;
        int s = min(N, (b + 1) * sqrtN - 1);
        int e = b * sqrtN;
        for(int i = s; i >= e; i--){
            if(dist_cnt[i] > 0) return i;
        }
    }
    return 0;
}

void erase_dist(int d){
    dist_cnt[d]--;
    if(dist_cnt[d] == 0)
        bucket_cnt[d / sqrtN]--;
}

void add_dist(int d){
    if(dist_cnt[d] == 0)
        bucket_cnt[d / sqrtN]++;
    dist_cnt[d]++;
}

int now(int x){
    if(pos[x].empty()) return 0;
    return pos[x].back() - pos[x].front();
}

void add_left(int idx){
    int x = v[idx];
    erase_dist(now(x));
    pos[x].push_front(idx);
    add_dist(now(x));
}

void add_right(int idx){
    int x = v[idx];
    erase_dist(now(x));
    pos[x].push_back(idx);
    add_dist(now(x));
}

void remove_left(int idx){
    int x = v[idx];
    erase_dist(now(x));
    pos[x].pop_front();
    add_dist(now(x));
}

void remove_right(int idx){
    int x = v[idx];
    erase_dist(now(x));
    pos[x].pop_back();
    add_dist(now(x));
}

void solve(){
    int s = 0, e = -1;

    for(int i = 0; i < Q; i++){
        int qs = query[i].s;
        int qe = query[i].e;

        while(e < qe) add_right(++e);
        while(e > qe) remove_right(e--);
        while(s < qs) remove_left(s++);
        while(s > qs) add_left(--s);

        answer[query[i].idx] = get_answer();
    }
}
```

`add/remove`를 빈 교과서형 자리표시자로 두지 않고, 실제 풀이의 값별 위치 덱과 거리 버킷 갱신을 그대로 남겼다. 다른 문제에서는 네 함수의 내부 상태만 문제에 맞게 바꾸고 바깥의 네 `while`문은 유지한다.

## 빈 화면 구현 순서

1. `add(i)`, `remove(i)`, `current_answer()`가 가능한지 먼저 설계한다.
2. 블록 크기 `B ≈ N / sqrt(Q)` 또는 `sqrt(N)`를 정한다.
3. 질의에 원래 인덱스를 붙여 정렬한다.
4. 빈 구간 `[0, -1]`에서 시작해 네 while문을 쓴다.
5. 결과를 `answer[id]`에 넣고 입력 순서로 출력한다.

## 자주 틀리는 지점

- 구간의 왼쪽/오른쪽 추가가 다른 자료구조라면 `add_left/right`를 분리한다.
- 빈 구간에서 빈도 0 상태가 실제 답 상태와 일치해야 한다.
- 답을 정렬된 질의 순서로 출력하지 않는다.
- 이 폴더의 `21064.cpp`는 빈 파일이라 복습 근거로 사용할 수 없다.
- 고급 dry-Mo/sweep 최적화는 기본 Mo를 완전히 복원한 뒤 공부한다.

## 대표 코드

- [13546.cpp](13546.cpp) — 값별 위치 덱과 거리 버킷을 함께 갱신하는 정석 Mo 골격
- [16264.cpp](16264.cpp) — 누적 상태를 결합한 Mo 응용
- [27937.cpp](27937.cpp) — 이동을 이벤트로 분해한 고급 dry-Mo/sweep 구현
