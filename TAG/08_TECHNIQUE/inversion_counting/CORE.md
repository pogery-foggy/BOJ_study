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

## 4. C++ 최소 구현 골격

```cpp
vector<int> tree(4 * U);

void update(int node, int s, int e, int idx) {
    if (idx < s || e < idx) return;
    ++tree[node];
    if (s == e) return;
    int m = (s + e) / 2;
    update(node * 2, s, m, idx);
    update(node * 2 + 1, m + 1, e, idx);
}

int query(int node, int s, int e, int l, int r) {
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return tree[node];
    int m = (s + e) / 2;
    return query(node * 2, s, m, l, r)
         + query(node * 2 + 1, m + 1, e, l, r);
}

long long answer = 0;
for (int cur : rank) {
    answer += query(1, 0, U - 1, cur + 1, U - 1);
    update(1, 0, U - 1, cur);
}
```

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

