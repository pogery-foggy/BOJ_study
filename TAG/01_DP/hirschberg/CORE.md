# Hirschberg 핵심 복원 노트

## 한 문장 기억

**LCS의 한 행만 앞·뒤에서 계산해 최적 분할점을 찾고, 두 구간을 재귀적으로 이어 붙여 `O(NM)` 시간과 `O(M)` 메모리로 문자열을 복원한다.**

## 언제 꺼내는가

- LCS·편집 거리의 값뿐 아니라 실제 경로/문자열도 필요하다.
- 일반 2차원 DP의 `O(NM)` 메모리가 제한을 넘는다.
- 한 축을 반으로 자르고, 다른 축의 최적 분할점을 전방/후방 행 DP로 결정할 수 있다.

## 핵심 상태와 불변식

- `forward[k]`: `A[as..mid)`와 `B[bs..bs+k)`의 LCS 길이.
- `backward[m-k]`: `A[mid..ae)`와 `B[bs+k..be)`의 LCS 길이.
- `forward[k] + backward[m-k]`가 최대인 `k`를 택하면 어떤 최적해 하나가 그 경계를 지난다.
- 각 행 계산은 `prev`, `cur` 두 줄만 유지한다.
- 모든 구간은 현재 코드처럼 반열린 구간 `[begin, end)`으로 통일한다.

## 내 코드 스타일 C++ 최소 구현 골격

스타일 근거: [18438.cpp](./18438.cpp)의 전역 문자열 `A`, `B`, `prefix()`/`suffix()` 함수 분리, 반열린 구간 `[as, ae)`, `n >> 1` 계산과 재귀 문자열 결합 방식을 보존했다.

```cpp
string A, B;

vector<int> prefix(int as, int ae, int bs, int be) {
    int m = be - bs;
    vector<int> cur(m + 1, 0), prev(m + 1, 0);
    for (int i = as; i < ae; i++) {
        cur[0] = 0;
        for (int j = 1; j <= m; j++) {
            if (A[i] == B[bs + j - 1])
                cur[j] = prev[j - 1] + 1;
            else
                cur[j] = max(prev[j], cur[j - 1]);
        }
        prev = cur;
    }
    return prev;
}

vector<int> suffix(int as, int ae, int bs, int be) {
    int m = be - bs;
    vector<int> cur(m + 1, 0), prev(m + 1, 0);
    for (int i = ae - 1; i >= as; i--) {
        cur[0] = 0;
        for (int j = 1; j <= m; j++) {
            if (A[i] == B[be - j])
                cur[j] = prev[j - 1] + 1;
            else
                cur[j] = max(prev[j], cur[j - 1]);
        }
        prev = cur;
    }
    return prev;
}

string hirschberg(int as, int ae, int bs, int be) {
    int n = ae - as;
    int m = be - bs;
    if (!n || !m) return "";
    if (n == 1) {
        for (int i = bs; i < be; i++) {
            if (B[i] == A[as]) return string(1, A[as]);
        }
        return "";
    }

    int amid = as + (n >> 1);
    vector<int> lk = prefix(as, amid, bs, be);
    vector<int> rk = suffix(amid, ae, bs, be);
    int maxi = -1, maxk = 0;
    for (int k = 0; k <= m; k++) {
        int value = lk[k] + rk[m - k];
        if (value > maxi) {
            maxi = value;
            maxk = k;
        }
    }
    int bmid = bs + maxk;
    return hirschberg(as, amid, bs, bmid) + hirschberg(amid, ae, bmid, be);
}
```

## 빈 화면 구현 순서

1. 먼저 롤링 LCS 한 행 함수가 정확한지 단독 검증한다.
2. 같은 함수를 뒤쪽에서 읽도록 만들어 suffix 길이를 구한다.
3. `A`의 중간 `mid`를 정한다.
4. 모든 `k=0..m`에 대해 `L[k]+R[m-k]`를 비교한다.
5. 두 반열린 구간으로 재귀 호출해 결과를 연결한다.
6. 빈 구간과 `A` 길이 1인 경우를 기저로 끝낸다.

## 자주 틀리는 지점

- suffix의 인덱스 `B[be-j]`와 합칠 때의 `R[m-k]`를 뒤섞는 것.
- `cur`를 다음 행 전에 올바르게 덮어쓰지 않는 것.
- `[l,r)`와 `[l,r]`를 섞어 문자 하나를 누락/중복하는 것.
- 두 문자열 중 더 긴 쪽을 열 방향으로 두어 메모리를 불필요하게 크게 쓰는 것.
- 편집 거리 버전에서 분할 비용과 실제 연산 복원 규칙을 LCS와 동일하다고 가정하는 것.

## 대표 로컬 풀이

- [18438.cpp](./18438.cpp): 전방/후방 롤링 LCS와 재귀 분할이 가장 선명한 구현
- [17161.cpp](./17161.cpp): 편집 거리로 확장한 Hirschberg
- [18440.cpp](./18440.cpp): bitset LCS와 결합한 고성능 변형
