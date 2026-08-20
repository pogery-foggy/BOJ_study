# SCC(강한 연결 요소) 핵심 복원 노트

## 한 문장 기억

**DFS 중 아직 스택에 남은 정점으로 돌아갈 수 있는 최소 방문 순서를 전파하고, 자기 방문 순서와 같아지는 정점에서 하나의 SCC를 꺼낸다.**

## 언제 꺼내는가

- 방향 그래프에서 서로 왕복 가능한 정점들을 묶는다.
- SCC를 한 정점으로 압축해 DAG의 시작점/진입차수/DP를 구한다.
- 2-SAT의 모순 판정과 해 복원에 사용한다.

## 핵심 상태와 불변식

- `order[u]`: DFS 방문 순서.
- `low`: `u`에서 DFS 간선과 아직 SCC가 확정되지 않은 정점을 통해 닿는 최소 방문 순서.
- 스택에는 방문했지만 아직 어느 SCC에도 확정되지 않은 정점만 있다.
- `low == order[u]`이면 `u`까지 pop한 정점들이 정확히 한 SCC다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [2150.cpp](./2150.cpp)의 전역 `stack<int> group`, `check`/`is_group`/`edge`, `idx`/`parent`/`child` 명명과 SCC를 `temp` 벡터로 꺼내는 재귀 `dfs()` 구조를 축약했다.

```cpp
stack<int> group;
int check[10001];
bool is_group[10001];
vector<int> edge[10001];
vector<vector<int>> groups;
int num;

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
            temp.push_back(cur);
            if (cur == idx) break;
        }
        groups.push_back(temp);
    }
    return parent;
}
```

## 빈 화면 구현 순서

1. 방향 인접 리스트를 만든다.
2. 방문 시 순서를 기록하고 스택에 넣는다.
3. 미방문 자식은 재귀 반환 low, 미완료 방문 정점은 order로 최솟값을 갱신한다.
4. 자기 order가 low이면 자기까지 pop해 같은 SCC 번호를 준다.
5. 모든 정점에서 미방문 DFS를 시작한다.
6. 필요하면 SCC 사이 중복 간선을 제거해 압축 DAG를 만든다.

## 자주 틀리는 지점

- 이미 SCC가 끝난 정점의 방문 순서까지 low에 반영하는 것.
- 자식 DFS의 반환값과 이미 방문한 이웃의 `order`를 구분하지 않는 것.
- 스택 포함 여부와 단순 방문 여부를 하나의 bool로 섞는 것.
- SCC 번호가 위상순인지 역위상순인지 확인하지 않고 후속 로직에 사용하는 것.
- 깊은 그래프에서 재귀 스택 한도를 확인하지 않는 것.

## 대표 로컬 풀이

- [2150.cpp](./2150.cpp): SCC 구성원을 정렬해 출력하는 Tarjan 기본형
- [4196.cpp](./4196.cpp): SCC 압축 뒤 시작 요소 수를 세는 응용
- [1506.cpp](./1506.cpp): 각 SCC 안의 최소 비용 집계
- [26146.cpp](./26146.cpp): 전체가 하나의 SCC인지 판정
