#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 100001
using namespace std;

// log 100000 은 16.x 대충 17번
// 17 * 100000 * 2
// C는 A에 대한 B숫자들의 위치
int A[MAX_N],B[MAX_N],index[MAX_N],N,C[MAX_N];

void init() {
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> A[i];
        index[A[i]] = i;
    }
    for(int i = 0 ; i < N; i++){
        cin >> B[i];
        C[i] = index[B[i]];
    }
}

void solve() {
    vector<int> v;
    for (auto a : C) {
        if (v.empty() || v.back() < a)
            v.push_back(a);
        else
            *upper_bound(v.begin(), v.end(), a - 1) = a;
    }
    cout << v.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}