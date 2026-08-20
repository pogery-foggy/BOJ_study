# LIS 핵심 복원 노트

## 한 문장 기억

**길이별로 가능한 가장 작은 마지막 값을 유지하고, 새 값이 들어갈 첫 위치를 이분 탐색하면 LIS 길이를 `O(N log N)`에 구한다.**

## 언제 꺼내는가

- 원래 순서를 유지한 채 엄격 증가/비감소 부분수열의 최장 길이를 구한다.
- `O(N^2)`의 모든 이전 원소 비교가 느리다.
- 정렬된 한 축에서 다른 축의 LIS를 구하는 형태(전깃줄, 교차 제거)다.

## 핵심 상태와 불변식

- `tails[len]`: 길이 `len+1`인 증가 부분수열 중 가능한 최소 마지막 값.
- `tails` 자체는 대개 실제 LIS가 아니지만 길이는 정확하다.
- 엄격 증가에는 `lower_bound(tails, x)`, 비감소에는 `upper_bound(tails, x)`를 쓴다.
- 복원 시 각 원소의 이전 원소 인덱스 `prev[i]`와 길이별 마지막 원소 인덱스 `last[len]`를 저장한다.

## C++ 최소 구현 골격

[12015.cpp](./12015.cpp)의 `upper_bound(a-1)` 아이디어를 일반적인 `lower_bound`로 표현하고, [14003.cpp](./14003.cpp)의 복원을 원소 인덱스 기준으로 고정한 형태다.

```cpp
vector<int> tails, last, prev(n, -1);

for (int i = 0; i < n; ++i) {
    int pos = lower_bound(tails.begin(), tails.end(), a[i]) - tails.begin();
    if (pos == (int)tails.size()) {
        tails.push_back(a[i]);
        last.push_back(i);
    } else {
        tails[pos] = a[i];
        last[pos] = i;
    }
    if (pos > 0) prev[i] = last[pos - 1];
}

vector<int> seq;
for (int cur = last.back(); cur != -1; cur = prev[cur]) seq.push_back(a[cur]);
reverse(seq.begin(), seq.end());
```

## 빈 화면 구현 순서

1. 엄격 증가인지 비감소인지 문장으로 확인한다.
2. `tails`의 의미를 “길이별 최소 끝값”으로 적는다.
3. 각 `x`의 교체 위치를 `lower_bound`/`upper_bound`로 찾는다.
4. 길이만 필요하면 `tails`만 유지한다.
5. 복원이 필요하면 갱신 전에 `prev[i]=last[pos-1]`, 이후 `last[pos]=i`를 기록한다.
6. 쌍 문제라면 첫 축 정렬 시 동률의 두 번째 축 정렬 규칙을 먼저 정한다.

## 자주 틀리는 지점

- 엄격 증가와 비감소에서 탐색 함수를 반대로 고르는 것.
- `tails`를 실제 부분수열로 출력하는 것.
- 복원용 이전 인덱스를 길이별 배열에만 저장해 이후 교체로 연결이 깨지는 것.
- 쌍 정렬의 동률 처리 때문에 같은 첫 좌표를 여러 번 선택하는 것.
- 제거할 항목을 구할 때 LIS에 포함된 원본 인덱스를 잃는 것.

## 대표 로컬 풀이

- [12015.cpp](./12015.cpp): 길이만 구하는 `O(N log N)` LIS
- [14003.cpp](./14003.cpp): 수열 복원을 시도한 구현
- [2568.cpp](./2568.cpp): 전깃줄 정렬 뒤 LIS 적용
- [1965.cpp](./1965.cpp): 작은 제한에서 확인하기 좋은 기본형

