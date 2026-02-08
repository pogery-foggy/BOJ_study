#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#define MAX_N 10
using namespace std;

int dp[1 << MAX_N];
int arr[MAX_N];
int N;
void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    memset(dp, -1, sizeof(dp));
}

int fnd(int is_visit) {
    if (!is_visit)
        return dp[0] = 0;
    if (dp[is_visit] != -1)
        return dp[is_visit];

    for (int i = 0; i < N; i++) {
        if (!(is_visit & (1 << i)))
            continue;
        // 얻을 점수 계싼 구간
        int cur = i;
        int l = -1;
        int r = -1;
        for (int j = cur + 1; j < N; j++)
            if (is_visit & (1 << j)) {
                r = j;
                break;
            }
        for (int j = cur - 1; j >= 0; j--)
            if (is_visit & (1 << j)) {
                l = j;
                break;
            }
        int point = 0;
        // cout << print_bits(is_visit)<< " " << cur << " " << l << " " << r <<"\n";
        if (l != -1 && r != -1)
            point = arr[l] * arr[r];
        else if (l != -1)
            point = arr[l];
        else if (r != -1)
            point = arr[r];
        else
            point = arr[cur];
        dp[is_visit] = max(dp[is_visit], point + fnd(is_visit ^ (1 << i)));
    }
    return dp[is_visit];
}

int solve() { return fnd((1 << N) - 1); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        cout << "#" << testcase + 1 << " " << solve() << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}

/* 결국 tsp처럼 dp비트마스킹인가 근데 topdown인가 bottomup인가?
0001
0010
0100
1000
다음거 볼때 if(is_visit & 1 << i) continue;
bottom up으로 가보자 아니다
top down
타고 타고 전부 터져있는 상태에서 하나만 남고
그러면 dp[visit] = max(dp[visit], cur_cost+tsp(visit ^ (1<<i)))
그러면 방문체크를 !(visit & 1<<i)
그러면 dp는 visit만큼 있을때 내가 얻을 수 있는 최대값
-> 그러면 visit 0이면 터트릴 수 있는 게 없으니 0
그러면 cout << dp((1<<N)-1);
*/