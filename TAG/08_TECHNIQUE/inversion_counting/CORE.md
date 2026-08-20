# 역전쌍 세기 핵심

## 1. 한 문장 기억

왼쪽부터 값을 넣으면서 이미 본 값 중 현재보다 큰 값의 개수를 누적하면 모든 역전쌍을 O(N log N)에 센다.

## 2. 언제 꺼내는가

- `i<j`인데 `a[i]>a[j]`인 쌍의 수를 구한다.
- 두 순열의 교차선 개수를 한쪽 순서에 대한 다른 쪽 인덱스로 바꿀 수 있다.
- 각 원소가 현재까지 몇 등인지 온라인으로 출력한다.

## 3. 핵심 상태 / 불변식

- i번째 처리 직전 트리에는 `a[0..i-1]`의 빈도만 들어 있다.
- 현재 압축 좌표가 `cur`이면 오른쪽 구간 `(cur, max]`의 합이 앞선 더 큰 값의 수다.
- 답은 최대 O(N²)이므로 `long long`으로 누적한다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [7578.cpp](./7578.cpp)의 `#define MAX_N`, 전역 세그먼트 트리와 값→인덱스 배열, `(s,e,node,...)` 순서의 재귀 함수, `node << 1` 자식 표기를 축약했다.

```cpp
#define MAX_N 500001

int tree[MAX_N * 4];
int fnd_idx[1000001];
vector<pair<int, int>> arr;
int N;

void update(int s, int e, int node, int idx) {
    if (idx < s || e < idx)
        return;
    tree[node]++;
    if (s != e) {
        int mid = (s + e) >> 1;
        update(s, mid, node << 1, idx);
        update(mid + 1, e, node << 1 | 1, idx);
    }
}

long long sum(int s, int e, int l, int r, int node) {
    if (r < s || e < l)
        return 0;
    if (l <= s && e <= r)
        return tree[node];
    int mid = (s + e) >> 1;
    return sum(s, mid, l, r, node << 1)
         + sum(mid + 1, e, l, r, node << 1 | 1);
}

void solve() {
    long long answer = 0;
    for (int i = 0; i < N; i++) {
        int cur = arr[i].second;
        update(0, N - 1, 1, cur);
        answer += sum(0, N - 1, cur + 1, N - 1, 1);
    }
    cout << answer;
}
```

[7578.cpp](./7578.cpp)처럼 `update` 뒤에 오른쪽 구간을 묻는다. 현재 위치 `cur`은 질의 범위 `cur + 1 ... N - 1`에 포함되지 않으므로 자기 자신은 역전쌍으로 세지 않는다.

## 5. 빈 화면 구현 순서

1. 두 순열 문제면 첫 순열의 값→위치 맵을 만든다.
2. 값 범위가 크면 좌표 압축한다.
3. 트리가 저장할 것을 “지금까지 등장한 빈도”로 정의한다.
4. 현재보다 큰 구간을 질의한다.
5. 현재 위치를 1 증가시킨다.
6. 정렬 배열은 0, 역정렬 배열은 `N(N-1)/2`인지 확인한다.

## 6. 자주 틀리는 지점

- 현재 원소를 먼저 업데이트하고 `>=cur`를 질의해 자기 자신을 세는 실수.
- `cur+1` 경계가 U가 되는 빈 구간을 처리하지 않는 실수.
- 답을 `int`에 저장하는 실수.
- 두 배열의 실제 값 대신 각 배열의 인덱스를 독립적으로 압축해 대응을 잃는 실수.

## 7. 내 코드에서 다시 보기

- [7578.cpp](./7578.cpp): 첫 배열의 위치 맵으로 두 번째 배열을 바꾸고 교차선을 계산
- [2517.cpp](./2517.cpp): 좌표 압축 후 앞선 더 큰 원소 수로 현재 등수 계산
- [1615.cpp](./1615.cpp): 간선 정렬과 역전쌍을 결합한 교차 개수
