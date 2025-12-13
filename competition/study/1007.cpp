#include <iostream>
#include <cmath>
#define INF 2100000000000
using namespace std;

int n;
int x[20], y[20];
long long mx, cur_x, cur_y;
int cnt1, cnt2;

// int pm[20];
// void dfs(int total, plus, minus){
//     if(total == N) {
//         최소값계산;
//         return;
//     }

//     for(int i = 0; i < N; i++){
//         if(!pm[i]) continue;
//         if(plus < 2/N){
//             더하기
//             dfs(total+1, plus+1,minus);
//             복원
//         }
//         if(minus < 2/N){
//             빼기
//             dfs(total+1,plus,minus+1);
//             복원
//         }
//     }   
// }

void dfs(int d = 0) {
    if (d == n) {
        mx = min(mx, cur_x * cur_x + cur_y * cur_y);
        return;
    }
    if (cnt1 < n / 2) {
        cur_x += x[d];
        cur_y += y[d];
        cnt1++;
        dfs(d + 1);
        cur_x -= x[d];
        cur_y -= y[d];
        cnt1--;
    }
    if (cnt2 < n / 2) {
        cur_x -= x[d];
        cur_y -= y[d];
        cnt2++;
        dfs(d + 1);
        cur_x += x[d];
        cur_y += y[d];
        cnt2--;
    }
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    mx = INF;
}

void solve() {
    dfs();
    cout << sqrt(mx) << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed;
    cout.precision(6);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}