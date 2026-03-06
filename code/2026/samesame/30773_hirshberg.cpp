#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

/* 팰린드롬 만들기 */
// 추가 길이 자체는 s.size-LCS(s, reverse(s)).size
// 팰린드롬 자체가
// 절반을 기준으로 같은거
// 그럼 s를 어떤 중앙값 기준으로 두개로 나눈뒤
// 하나를 reverse하고
// 둘 사이의 편집거리를 구하면 되지 않을까
// 이때 중요한거 홀수 길이의 팰린드롬 만들찌
// 짝수 길이의 팰린드롬 만들지
// 어케판단? 시작을 어케나눔?
// 중심구하는 함수는 일단 나중에

string A, B;  
string L, R; 
int N;
bool is_center;  
int center;   
int mini;

void init() {
    cin >> A;
    N = A.size();
    B = A;
    reverse(B.begin(), B.end());
    mini = 2100000000;
    is_center = true;
    center = 0;
}

void append(char ch) {
    L.push_back(ch);
    R.push_back(ch);
}

// dp자체는 편집거리랑 똑같 edi가 좀 달라짐 edit가 안됨
vector<int> prefix(int as, int ae, int bs, int be) {
    int m = be - bs;
    vector<int> cur(m + 1), prev(m + 1);

    for (int j = 0; j <= m; j++) prev[j] = j; 

    int row = 0;
    for (int i = as; i < ae; i++) {
        row++;
        cur[0] = row; 
        for (int j = 1; j <= m; j++) {
            int del = prev[j] + 1;
            int ins = cur[j - 1] + 1;
            int edi = prev[j - 1] + (A[i] == B[bs + j - 1] ? 0 : 210000000);
            cur[j] = min(del, ins);
            cur[j] = min(cur[j], edi);
        }
        prev.swap(cur);
    }
    return prev;
}

vector<int> suffix(int as, int ae, int bs, int be) {
    int m = be - bs;
    vector<int> cur(m + 1), prev(m + 1);

    for (int j = 0; j <= m; j++) prev[j] = j;

    int row = 0;
    for (int i = ae - 1; i >= as; i--) {
        row++;
        cur[0] = row;
        for (int j = 1; j <= m; j++) {
            int del = prev[j] + 1;
            int ins = cur[j - 1] + 1;
            int edi = prev[j - 1] + (A[i] == B[be - j] ? 0 : 210000000);
            cur[j] = min(del, ins);
            cur[j] = min(cur[j], edi);
        }
        prev.swap(cur);
    }
    return prev;
}

// A : [0, center), B = [center+1or0, e) 이제 홀수냐에 따라 b시작이 다름
void hirschberg(int as, int ae, int bs, int be) {
    int n = ae - as;
    int m = be - bs;

    if (n == 0) { // b추가
        for (int j = bs; j < be; j++) append(B[j]);
        return;
    }
    if (m == 0) { // a삭제(추가)
        for (int i = as; i < ae; i++) append(A[i]);
        return;
    }

    if (n == 1) {
        int pos = -1;
        for (int j = bs; j < be; j++) {
            if (B[j] == A[as]) { pos = j; break; }
        }
        if (pos == -1) {
            append(A[as]);
            for (int j = bs; j < be; j++) append(B[j]);
        } else {
            for (int j = bs; j < pos; j++) append(B[j]);
            append(A[as]);
            for (int j = pos + 1; j < be; j++) append(B[j]);
        }
        return;
    }

    if (m == 1) { // 얘는 삭제시퀀스라 반대로
        int pos = -1;
        for (int i = as; i < ae; i++) {
            if (A[i] == B[bs]) { pos = i; break; }
        }
        if (pos == -1) {
            for (int i = as; i < ae; i++) append(A[i]);
            append(B[bs]);
        } else {
            for (int i = as; i < pos; i++) append(A[i]);
            append(B[bs]);
            for (int i = pos + 1; i < ae; i++) append(A[i]);
        }
        return;
    }

    int amid = as + (n >> 1);

    vector<int> lk = prefix(as, amid, bs, be);
    vector<int> rk = suffix(amid, ae, bs, be);

    int mini = 210000000;
    int mink = 0;
    for (int k = 0; k <= m; k++) {
        int value = lk[k] + rk[m - k];
        if (value < mini) {
            mini = value;
            mink = k;
        }
    }

    int bmid = bs + mink;
    hirschberg(as, amid, bs, bmid);
    hirschberg(amid, ae, bmid, be);
}


// 중심을 찾자
// dp[i][j] = lcs(A[0,i), B[0,j) )의 길이
// dp[0][j] = 0, dp[i][0] = 0
// a[i-1] == b[j-1] 이면 dp[i][j] = dp[i-1][j-1] + 1
// else min(dp[i-1][j], dp[i][j-1])

// 이때 B를 revese했고 이때 둘의 LCS를 구하면 삽입값을 알 수 있음
// 짝수일땐 N - LCS * 2
// 홀수일땐 N - LCS * 2 - 1 (센터 하나)

// 0~i와 (N-i)~N 나누면 k = dp[i][N-i]
// k = cur[N-i];
void fnd_center(int i, vector<int> cur) {
    // even
    int j = N - i;
    if (0 <= j && j <= N) {
        int k = cur[j];
        int ins = N - 2 * k;
        if (ins < mini) {
            mini = ins;
            is_center = false;
            center = i;
        }
    }

    // odd
    if (i < N) {
        int j = N - 1 - i;
        int k = cur[j];
        int ins = N - (2 * k + 1);
        if (ins < mini) {
            mini = ins;
            is_center = true;
            center = i;
        }
    }
}

void choose_center() {
    vector<int> prev(N + 1, 0), cur(N + 1, 0);

    fnd_center(0, prev);

    for (int i = 1; i <= N; i++) {
        cur[0] = 0;
        for (int j = 1; j <= N; j++) {
            if (A[i - 1] == B[j - 1]) cur[j] = prev[j - 1] + 1;
            else cur[j] = max(prev[j], cur[j - 1]);
        }
        fnd_center(i, cur);
        prev.swap(cur);
    }
}

void solve() {
    L.reserve(N);
    R.reserve(N);

    choose_center();
    int lenB = is_center ? (N - 1 - center) : (N - center);
    hirschberg(0, center, 0, lenB);

    string answer;
    answer.reserve(L.size() * 2 + 1);
    if (is_center) {
        answer += L;
        answer.push_back(A[center]);
        for (auto it = R.rbegin(); it != R.rend(); it++) 
            answer.push_back(*it);
    } else {
        answer += L;
        for (auto it = R.rbegin(); it != R.rend(); it++) 
            answer.push_back(*it);
    }

    cout << answer.size() - N << "\n" << answer << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}