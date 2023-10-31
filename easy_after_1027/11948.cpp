#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int a, b, c, d, e, f;
vector<int> fir, sec;
void init() {
    cin >> a >> b >> c >> d >> e >> f;
    fir.push_back(a);
    fir.push_back(b);
    fir.push_back(c);
    fir.push_back(d);
    sec.push_back(e);
    sec.push_back(f);
    sort(fir.begin(), fir.end());
    sort(sec.begin(), sec.end());
}

void solve() { cout << fir[1] + fir[2] + fir[3] + sec[1]; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}