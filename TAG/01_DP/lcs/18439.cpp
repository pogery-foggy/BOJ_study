#include <iostream>
#include <string>

using namespace std;

/* 18439 lcs 6
 * 필요한 것, set, shift, &, ^, |, -, count lcs
 * 50000 / 64 = 781.25 782개의 ull필요함
 */

typedef unsigned long long ull;
struct Bitset {
    ull block[782];
    // block을 찾고(/64), pos를 &11111111 해서 block내의 위치를 찾음
    void set(int pos) { block[pos >> 6] |= (1ULL << (pos & 63)); }
    void shift() {
        for (int i = 781; i >= 0; i--) {
            // 50000글자 까지라 781에서 782의 캐리가 일어날 일 없음
            bool carry = ((block[i] >> 63) & 1 ? true : false);
            block[i] <<= 1;
            if (carry)
                block[i + 1] |= 1;
        }
        block[0] |= 1;
    }
    Bitset operator&(const Bitset &t) const {
        // a&b는 비파괴가 되어야 함. 그렇기 때문에 새로운 c를 선언, 그렇기 때문에 oper& const
        // 파괴로 하고 싶으면 &=을 바꿀 것.
        Bitset c;
        for (int i = 0; i < 782; i++) {
            c.block[i] = block[i] & t.block[i];
        }
        return c;
    }
    Bitset operator|(const Bitset &t) const {
        Bitset c;
        for (int i = 0; i < 782; i++) {
            c.block[i] = block[i] | t.block[i];
        }
        return c;
    }
    Bitset operator^(const Bitset &t) const {
        Bitset c;
        for (int i = 0; i < 782; i++) {
            c.block[i] = block[i] ^ t.block[i];
        }
        return c;
    }
    Bitset operator-(const Bitset &t) const {
        // carry 주의
        Bitset c;
        bool carry = 0;                 // bool로 하면 안되나? bool로 해야함 overflow때문에
        for (int i = 0; i < 782; i++) { // 0부터 시작하면 carry때문에 안됨
            c.block[i] = block[i] - t.block[i];
            if (carry)
                c.block[i]--;
            carry = (block[i] < t.block[i] || ((block[i] == t.block[i]) & carry));
            // overflow code carry = (block[i] <= t.block[i] + carry? 1 : 0); // this와 t같으면 carry가 있을때 carry발생
        }
        return c;
    }
    size_t count() {
        size_t total = 0;
        for (int i = 0; i < 782; i++) {
            total += __builtin_popcountll(block[i]);
        }
        return total;
    }
};

Bitset alpha[26], candidat, previou; // candidate, previous
string s1, s2;
void init() {
    cin >> s1 >> s2;
    for (int i = 0; i < s1.size(); i++) {
        alpha[s1[i] - 'A'].set(i);
    }
}
void solve() {
    for (auto a : s2) {
        // 이전까지의 prefix_XOR과 현재 매칭될 수 있는 alpha를 or해서 후보군 특정
        candidat = previou | alpha[a - 'A'];
        // i-1에서 현재의 i로 끌어오기
        previou.shift();
        // 아래 주석참조
        previou = candidat ^ (candidat & (candidat - previou));
    }
    cout << previou.count();
}

int main() {
    init();
    solve();
    return 0;
}

/*
`dp` 전체를 직접 저장하는 DP”가 아니라
 "각 열 j에서 **LCS 값이 증가하는 지점들(경계)**만 비트로 저장해 두고, 그 경계를 갱신하면서 마지막에 LCS 길이를 복원하는 알고리즘"

그래서 `previous`, `candidate`은 “값 그 자체”가 아니라 **증가 패턴**을 들고 있는 비트셋이라서,

s1을 앞에서부터 한 글자씩 읽으면서
s2에서 어디까지 subsequence를 만들 수 있는지를 표시해보자

예시가 s1="A", s2 = "BA"라고 할때,
기존의 dp는 dp[1][1] = 0 ("A","B")
                       dp[1][2] = 1 ("A", "BA")
        좀 더 말로 풀어보면 s1의 첫번째 글자까지와 s2의 첫번째 글자까지 매칭되는 것(LCS)은 0
                                          s1의 첫번째 글자까지와 s2의 두번째 글자까지 매칭되는 것(LCS)은 1
        !!!여기서 LCS길이가 1 이상이 되는 지점만 표시해 본다면 어떻게 될까?
        첫번째, j = 0일때 LCS길이는 0이었지, j = 1일때, LCS길이는 1이었지.
        그럼 이거를 비트로 표현해보면 10 ( 오른쪽부터 0번째 인덱스)
        이 설명이랑 비슷하게,

- 행: A에서 어디까지 봤는지 (`i`) ( A의 prefix 길이)
- 열: B에서 어디까지 봤는지 (`j`) ( B의 prefix 길이)

  [previousious]는 “i까지 진행했을 때, LCS 길이가 1 이상인 열의 집합(B의 인덱스의 집합)"을 들고있다.
        라는 느낌.

이때 열의 집합은 “지금 보고 있는 A의 prefix에 대해, B의 어느 열들 j에서 LCS길이가 어떤 기준 이상이 되는지 표시한 j 인덱스 들의 집합.
그래서 previous는 다시말하면, A의 어떤 prefix 길이 i가 고정된 상태에서, B의 각 인덱스 j마다 “여기에 LCS길이가 증가하는 경계가 있다/없다”를 담셋

### **candidate = arr[a-'A']|previous;**

**arr[a] "이번 문자로 새로 match된자리"
previous "이미 LCS가 형성돼 있는 위치들(이전까지 축적된 match)"   // match를 기존에 설명하자.
candidate = "이번 문자 처리에서 고려해야할 모든자리 == 지금 시점에 후보가 될 수 있는 모든 위치"**
                그렇기 때문에 arr[a](새로운자리)와 prev(기존까지자리)를 'or'연산 한것

### prev.shift();

기존 dp에서 (보기쉽게 s1 == A,s2 == B로 명칭 변경)
if(A[i-1] == B[i-1]){ dp[i][j] = dp[i-1][j-1] + 1; }
에서 대각선으로 값은 가져옴 즉 이전 행과 열에서 가져온건데,
비트셋 버전에서는 prev가 이전 행의 정보를 들고있음. (정확히는 prefix_XOR)
따라서 prev를 shift하는거, shift를 하는 이유는 prev는 i-1행이었고, 이번행은 i행이니까.

예를들어 previous가 {0,1,0,0,1}이라고 할때,

dp[i][j]를 계산할 때 필요한 값은 dp[i-1][j-1]이고,

즉 이전 행(previous)의 j-1 위치의 값을 써야함.

j=2, j=5 이므로 previous의 1, 4위치의 값을 써야 하는 거.

**즉, 이전 행에서(j-1) 있던 정보를, 이번 행의 j자리로 옮기기 위해 왼쪽 shift한다.**
previous를 복사해서 쓰는 것이 아니라 아예 shift해도 괜찮은 이유는 이미 윗줄에서 써먹음.
그래서 이제 previous “대각선 맞춘 이전 행”이라는 새 의미를 가지게 된 것.
결국 아랫줄에서 previous = … 하면서 새 행의 경계 패턴이 됐음.

### candidate-previous

candidate, previous가 들고 있는 정보는 직접적인 dp[i][j]가 아니라,

모노톤 논디크리징인 **dp** **배열의 증가가 일어나는 경계들을 비트 패턴 하나에 잘 encode 해 놓은 것**

encode하다 : 원래는 2차원/정수 배열에 들어 있던 정보를 비트 하나하나에 **압축해서 표현한다.**

(증가경계: A의 i번째 문자와 B의 어떤 위치 j의 문자가 같아서, LCS 길이가 **진짜로 1 늘어나는 지점**)

```python
비트를 4개만 쓰는 예제
j = 0,1,2,3
그리고 이전 행에서 증가 경계가 j = 1,3에 있다고 가정할 때
1010   (왼쪽이 높은 j)
그리고 가능해진 후보는 1110이라고 해보자, 이 말은 이번에 새로 매칭된 게 ?1?0 이라는
그러면
previous = 1010
candidate = 1110

이때 candidate - previous를 해보면 0100
이번 단계에서 실제로 새로운 증가가 시작되는 지점과 연결됨.
후보에서 이전을 빼면서 이전까지의 부분은 약간 상쇄되고,
즉 처음으로 차이가 나는 지점에서 1이 튀어나오는 효과
```

정리하자면 candidate - previous 는 “경계 후보”를 가진 정수고

**이걸 candidate & (candidate -previous)하면서 “실제 후보 위치 중에서 증가 지점”만 남기는 것.**

```python
이전 설명
둘 다 증가 경계의 누적 패턴 같은 것을 들고 있고,
이 둘의 뺄셈을 하면
"어느 구간에서 새로 증가가 발생했는지"를 뽑아낼 수 있다.
코드/예제는 잠시 냅두고, 비트/정수 예시를 보자.

어떤 배열h[j]가 있고, 이게 monotone nondecreasing하다고 하자
(dp 값은 j가 커질수록 내려가지 않으니까 이런 성질을 가짐)
예를 들어 h = [0,0,1,1,2,2,]라고 할 때, "증가하는 지점"만 보고 싶다면?
increasing = [0,0,1,0,1,0]이고,
inc를 알면 h를 다시 복원 할 수 있음. ( increasing을 누적합 하면 되니까)

이제 비트에서 비슷한 짓을 해볼거임.
candidate, previous가 이런 종류의 누적 패턴에 대응되고(이런 종류가 h같은 monotone을 말하는거임? 아니면 incrasing처럼 증가하는 지점을 말하는 거임?)
```

## candidate ^ candidate & (candidate - previous)

**이제 toggle하면서 증가지점의 경계를 뽑는 것.**

toggle로 경계를 뽑는 것, 상태를 뒤집는 다는 것에 대한 예시를 들어보자면, 스위치가 네개 있다고 생각해보자

[OFF, OFF, ON, ON]

이때, 스위치가 ON→OFF되거나 OFF→ON되는 지점만 1로 표현해보자면

[0, 0, 1, 0]
이다. 그리고 이게 경계비트가 된다. 여기서는 candidate&(candidate-previous)가 된다.

자, 이제 토글 예시를 들 것이다. 실제 LCS 그대로는 아니지만, 다른 구간이 시작된다고 표시하는 감각을 보여주려 하는 것.

[OFF, OFF, ON, ON] 이전에 [OFF, OFF, OFF, OFF]이었다고 가정하자.

[0,0,1,1] 이전에 [0,0,0,0]이었던 것이다.

그러면 증가 경계 비트는 [0,0,1,0]이 된다 ( 3번째 에서만 증가)

정리하자면 현재 candidate는 [0,0,1,1], increase(candidate & (candidate-previous)) 는 [0,0,1,0]
그러면 candidate ^ increase = B라고 하면 B는 [0,0,0,1]가 나온다.

이때 S를 B의 prefix-XOR로 복원할 수 있다.

다시한번말하지만 다만 실제와는 살짝 다르고 toggle의 의미를 보여주기 위해 적은 것이므로 이 예시에 매몰되진 말자.  **S를 B의 prefix-XOR로 복원할 수 있다.**
그래서 previous, 즉 B를 계속 prefix-XOR해가지고 마지막에 count를 세면 S를 알 수 있는 것이다.
*/