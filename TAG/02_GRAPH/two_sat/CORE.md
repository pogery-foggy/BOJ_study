# 2-SAT 핵심 복원 노트

## 한 문장 기억

**절 `(a ∨ b)`를 두 함의 `¬a→b`, `¬b→a`로 바꾸고, 어떤 변수와 그 부정이 같은 SCC인지 검사한다.**

## 언제 꺼내는가

- 각 조건이 리터럴 두 개의 OR이고 전체 조건을 모두 만족해야 한다.
- 두 선택 중 하나, 양립 불가, 적어도 하나 같은 제약을 불리언 변수로 표현할 수 있다.
- 만족 가능 여부뿐 아니라 실제 참/거짓 배정도 필요하다.

## 핵심 상태와 불변식

- 한 변수의 참/거짓 리터럴을 인접한 두 ID로 두면 부정은 `id ^ 1`이다.
- `(a ∨ b)`가 거짓이 되는 두 경우를 막는 함의가 `¬a→b`, `¬b→a`다.
- `x`와 `¬x`가 같은 SCC면 서로를 강제하므로 모순이다.
- 배정은 SCC 압축 DAG의 역위상 순서에 맞춰 아직 미정인 리터럴과 그 부정을 반대로 정한다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [11281.cpp](./11281.cpp)의 전역 `group`/`edge`/`groups`/`SCC`와 재귀 Tarjan `dfs()`, 양수는 `a << 1`, 음수는 `(-a) << 1 | 1`로 바꾸는 삼항식, 부정을 `^ 1`로 구하는 방식을 보존했다.

```cpp
#define MAX_N 10001

stack<int> group;
int groups[MAX_N * 2], check[MAX_N * 2];
bool is_group[MAX_N * 2];
vector<int> edge[MAX_N * 2];
vector<vector<int>> SCC;
int answer[MAX_N * 2];
bool visit_answer[MAX_N * 2];
int N, M, num, scc_group_num;

void init() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a = a > 0 ? (a << 1) : ((-a) << 1 | 1);
        b = b > 0 ? (b << 1) : ((-b) << 1 | 1);
        edge[a ^ 1].push_back(b);
        edge[b ^ 1].push_back(a);
    }
}

int dfs(int idx) {
    check[idx] = ++num;
    group.push(idx);
    int parent = check[idx];

    for (auto a : edge[idx]) {
        int child = a;
        if (!check[child])
            parent = min(parent, dfs(child));
        else if (!is_group[child])
            parent = min(parent, check[child]);
    }

    if (parent == check[idx]) {
        vector<int> temp;
        while (true) {
            int cur = group.top();
            group.pop();
            is_group[cur] = true;
            groups[cur] = scc_group_num;
            temp.push_back(cur);
            if (cur == idx)
                break;
        }
        SCC.push_back(temp);
        scc_group_num++;
    }
    return parent;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        if (!check[i << 1])
            dfs(i << 1);
        if (!check[i << 1 | 1])
            dfs(i << 1 | 1);
    }

    for (int i = 1; i <= N; i++) {
        int t = i << 1;
        if (groups[t] == groups[t ^ 1]) {
            cout << 0;
            return;
        }
    }
    cout << 1 << "\n";

    for (auto a : SCC) {
        for (auto b : a) {
            if (!visit_answer[b]) {
                answer[b] = 1;
                answer[b ^ 1] = 0;
                visit_answer[b] = true;
                visit_answer[b ^ 1] = true;
            }
        }
    }
    for (int i = 1; i <= N; i++)
        cout << answer[i << 1] << " ";
}
```

현재 Tarjan 방식처럼 SCC를 **스택에서 빠져나온 순서(압축 DAG의 sink부터)** 저장했다면, [11281.cpp](./11281.cpp)처럼 그 순서대로 보며 미정 리터럴을 참·반대 리터럴을 거짓으로 둘 수 있다. SCC 번호 방향을 바꿨다면 배정 부등호도 바뀌므로 암기하지 말고 간단한 `(x)` 절로 검증한다.

## 빈 화면 구현 순서

1. 변수 `x`와 `¬x`의 ID 규칙을 정하고 `^1` 관계를 확인한다.
2. 각 절을 두 함의 간선으로 바꾼다.
3. 모든 `2N`개 리터럴의 SCC를 구한다.
4. 모든 변수에서 참/거짓 SCC가 같은지 검사한다.
5. 배정이 필요하면 SCC 생성 순서 또는 압축 DAG 위상순을 확인한다.
6. 아직 미정인 리터럴을 정할 때 반대 리터럴도 즉시 반대 값으로 둔다.

## 자주 틀리는 지점

- 음수 리터럴을 배열 인덱스로 직접 쓰는 것.
- OR 절의 함의를 `a→b`, `b→a`로 잘못 만드는 것.
- 정점 루프에서 참 또는 거짓 리터럴 한쪽을 빠뜨리는 것.
- SCC 번호 방향을 확인하지 않고 인터넷의 배정 부등호를 복사하는 것.
- 문제의 “적어도 하나/정확히 하나/동일/상이” 조건을 절로 잘못 옮기는 것.

## 대표 로컬 풀이

- [11281.cpp](./11281.cpp): Tarjan SCC와 실제 배정까지 포함한 구현
- [11280.cpp](./11280.cpp): 만족 가능 여부만 판정하는 기본형
- [3648.cpp](./3648.cpp): 특정 변수를 참으로 강제하는 절을 추가하는 응용
