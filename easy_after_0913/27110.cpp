#include <iostream>

using namespace std;

int N,A,B,C;

void init() {
    cin >> N;
    cin >> A >> B >>C;
}

void solve() {
    int total = 0;
    if(N>A) total += A;
    else total += N;
    if(N>B) total +=B;
    else total += N;
    if(N>C) total += C;
    else total += N;

    cout <<total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}