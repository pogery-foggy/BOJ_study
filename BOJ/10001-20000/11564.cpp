#include <iostream>

using namespace std;
long long k, a, b, answer;
long long ms, me, ps, pe;
void init() {
    cin >> k >> a >> b;
    if (a < 0) {
        me = -a;
        ps = 0;
    } else if (a == 0) {
        me = 0;
        ps = a;
    } else {
        me = -1;
        ps = a;
    }
    if (b < 0) {
        ms = -b;
        pe = -1;
    } else if (b == 0) {
        ms = 0;
        pe = b;
    } else {
        ms = 0;
        pe = b;
    }
    if (pe != -1 && me != -1) {
        answer++;
    }
}

void solve() {
    if (pe != -1) {
        long long temp = pe / k - ps / k;
        if (ps && !(ps % k))
            temp++;
        answer += temp;
    }
    if (me != -1) {
        long long temp = me / k - ms / k;
        if (ms && !(ms % k))
            temp++;
        answer += temp;
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}