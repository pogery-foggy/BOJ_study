#include <iostream>

using namespace std;
int N, K;
long long ckdl; 
void init() {
    cin >> N >> K;
    ckdl = 2*N - K*(K+1); // n = (k(k+1)/2)
}

void solve() {
    if(ckdl < 0) cout << -1;
    else if(ckdl % K == 0) cout << K-1;
    else cout << K;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}