#include <iostream>

using namespace std;
int n;
int x1, y1, x2, y2, cx, cy, cr;
int wlsdlq_cnt, xkfcnf_cnt;

void init() {
    cin >> x1 >> y1 >> x2 >> y2;
    cin >> n;
    wlsdlq_cnt = 0;
    xkfcnf_cnt = 0;
}

void solve() {
    for (int i = 0; i < n; i++) {
        cin >> cx >> cy >> cr;

        if ((cx - x1) * (cx - x1) + (cy - y1) * (cy - y1) < cr * cr)
            if ((cx - x2) * (cx - x2) + (cy - y2) * (cy - y2) > cr * cr)
                xkfcnf_cnt++;

        if ((cx - x1) * (cx - x1) + (cy - y1) * (cy - y1) > cr * cr)
            if ((cx - x2) * (cx - x2) + (cy - y2) * (cy - y2) < cr * cr)
                wlsdlq_cnt++;
    }
    cout <<  xkfcnf_cnt +  wlsdlq_cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}