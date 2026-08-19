#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
string A, B, answer;
void init() {
    cin >> A >> B;
}

void emit(char op, char ch) {
    answer.push_back(op);
    answer.push_back(' ');
    answer.push_back(ch);
    answer.push_back('\n');
}

/* levenshtein distance 압축 */
/* 
초기값
D[0][j] = j
D[i][0] = i
점화식
D[i][j] = min({D[i-1][j] + 1(삭제), D[i][j-1] + 1(삽입), D[i-1][j-1] + (s[i-1] = t[i-1]?0:1)}(수정복사))
*/

vector<int> prefix(int as, int ae, int bs, int be) {
    int m = be - bs;
    vector<int> cur(m+1), prev(m+1);
    int row = 0;
    for(int j = 0; j <= m; j++) prev[j] = j;

    for(int i = as; i < ae; i++){
        row++;
        cur[0] = row; // dp[i][0] = i;
        for(int j = 1; j <= m; j++){
            int del = prev[j] + 1;
            int ins = cur[j - 1] + 1;
            int edi = prev[j - 1] + (A[i] == B[bs + j - 1] ? 0 : 1); 
            cur[j] = min({del, ins});
            cur[j] = min({cur[j], edi});
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
             // 거꾸로
            int edi = prev[j - 1] + (A[i] == B[be - j] ? 0 : 1);
            cur[j] = min({del, ins});
            cur[j] = min({cur[j], edi});
        }
        prev.swap(cur);
    }
    return prev;
}
void hirschberg(int as, int ae, int bs, int be) {
    int n = ae - as;
    int m = be - bs;

    // n=0 b를 추가
    if (n == 0) { 
        for (int j = bs; j < be; j++) emit('a', B[j]);
        return;
    }
    // m=0 a를  삭제
    if (m == 0) {
        for (int i = as; i < ae; i++) emit('d', A[i]);
        return;
    }

    // n=1 있으면 그자리에 복사 아니면 첫글짜 수정
    if (n == 1) {
        int pos = -1;
        for (int j = bs; j < be; j++) {
            if (B[j] == A[as]) { 
                pos = j; 
                break; 
            }
        }
        if (pos == -1) { // 수정후 append
            emit('m', B[bs]);
            for (int j = bs + 1; j < be; j++) emit('a', B[j]);
        } else { // 있으면 복사
            for (int j = bs; j < pos; j++) emit('a', B[j]);
            emit('c', A[as]);
            for (int j = pos + 1; j < be; j++) emit('a', B[j]);
        }
        return;
    }

    if (m == 1) {
        int pos = -1;
        for (int i = as; i < ae; i++) {
            if (A[i] == B[bs]) { 
                pos = i; 
                break; 
            }
        }
        if (pos == -1) {
            emit('m', B[bs]);
            for (int i = as + 1; i < ae; i++) emit('d', A[i]);
        } else {
            for (int i = as; i < pos; i++) emit('d', A[i]);
            emit('c', B[bs]);
            for (int i = pos + 1; i < ae; i++) emit('d', A[i]);
        }
        return;
    }

    int amid = as + (n >> 1);
    vector<int> lk = prefix(as, amid, bs, be);
    vector<int> rk = suffix(amid, ae, bs, be);

    int mini = 2100000000;
    int mink = -1;
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
void solve() {
    answer.reserve(4 * (A.size() + B.size())); 
    hirschberg(0, A.size(), 0, B.size());
    cout << answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}