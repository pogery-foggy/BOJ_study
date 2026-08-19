#include <algorithm>
#include <iostream>
#define MAX_N 501
#define INF (1LL << 62)
using namespace std;
typedef long long ll;

// 수평 먼저 짜르면 위를 서브 문제로 바꿀 수 있음.
// 수직 먼저, 가장 왼쪽이나 가장 오른쪽만 찾으면 됨. 
// 그러면 그 왼쪽과 오른쪽에 버티컬이 없다는 게 증명되니까 
// 이제 짜른 뒤에 수평보는 문제로 바뀜
/*
중요한 게, 수직을 짜를 때 왼쪽부터, 오른쪽부터가 아니라
두개로 나뉜다는 거임
(a) 수평 먼저  -> dpH[p][q]

(b) 수직 먼저
    base-reaching vertical 중 "가장 오른쪽" 것을 하나 고른다.
    그 경계를 t 라고 하면,
        - 왼쪽 부분 [p, t) 는 다시 왼쪽 anchored 서브문제  -> dpL[p][t]
        - 오른쪽 부분 [t, q) 는 더 이상 base-reaching vertical 이 없으므로
          첫 절단이 수평으로 강제된 상태                -> dpH[t][q]
        - 새로 넣은 수직선 길이 = valley[t] - valley[p]

        따라서
        dpL[p][q] = min( dpH[p][q], dpL[p][t] + (valley[t]-valley[p]) + dpH[t][q] )
        를 모든 가능한 t 에 대해 최소화한다.
*/
int N, M;
ll w[MAX_N], h[MAX_N];
ll x_pos[MAX_N];
ll valley[MAX_N]; // 수직
ll min_height[MAX_N][MAX_N]; // 수평

ll dpH[MAX_N][MAX_N]; // 수평
ll dpL[MAX_N][MAX_N]; // 왼쪽
ll dpR[MAX_N][MAX_N]; // 오른쪽

void init(){
    cin >> N;

    M = 0;
    // 높이가 같으면 한블럭으로 취급
    for(int i = 0; i < N; i++){
        int ww, hh;
        cin >> ww >> hh;

        if(M > 0 && h[M - 1] == hh){
            w[M - 1] += ww;
        } 
        else{
            w[M] = ww;
            h[M] = hh;
            M++;
        }
    }

    // 각 블럭 시작위치 저장
    x_pos[0] = 0;
    for(int i = 0; i < M; i++)
        x_pos[i + 1] = x_pos[i] + w[i];

    // 수직으로 자르면 미리 구하기
    valley[0] = 0;
    valley[M] = 0;
    for(int i = 1; i < M; i++)
    valley[i] = min(h[i - 1], h[i]);

    // 초기화
    for(int i = 0; i <= M; i++){
        for(int j = 0; j <= M; j++){
            dpH[i][j] = INF;
            dpL[i][j] = INF;
            dpR[i][j] = INF;
            min_height[i][j] = INF;
        }
    }
    // 수평으로 자르면 미리 구하기
    for(int p = 0; p < M; p++){
        ll cur = INF;
        for(int q = p + 1; q <= M; q++){
            cur = min(cur, h[q - 1]);
            min_height[p][q] = cur;
        }
    }
}


// 강제로 수평으로 짜르기
ll horizontal(int p, int q){
    ll cut = min_height[p][q];
    ll ret = 0;

    int i = p;
    while (i < q){
        // 높이가 cut 이하이면 이번 수평선 위로 남지 않는다.
        if(h[i] <= cut){
            i++;
            continue;
        }

        int l = i;
        while (i < q && h[i] > cut)
            i++;
        int r = i;
        ret += x_pos[r] - x_pos[l];

        // 남는 서브문제
        if(l == p){
            ret += dpR[l][r];
        } else if(r == q){
            ret += dpL[l][r];
        } else {
            ret += min(dpL[l][r], dpR[l][r]);
        }
    }
    return ret;
}

ll vertical_left(int p, int q) {
    ll base = valley[p];
    ll ret = dpH[p][q];

    for (int t = p + 1; t < q; t++) {
        if (valley[t] <= base)
            continue;
        if (dpL[p][t] == INF || dpH[t][q] == INF)
            continue;

        // 남은 왼쪽 버티컬 + 남은 오른쪽은 버티컬없어서 수평 + 높이
        ret = min(ret, dpL[p][t] + dpH[t][q] + (valley[t] - base));
    }
    return ret;
}

// 얘는 대칭
ll vertical_right(int p, int q) {
    ll base = valley[q];
    ll ret = dpH[p][q];

    for (int t = p + 1; t < q; t++) {
        if (valley[t] <= base)
            continue;
        if (dpH[p][t] == INF || dpR[t][q] == INF)
            continue;

        ret = min(ret, dpH[p][t] + dpR[t][q] + (valley[t] - base));
    }
    return ret;
}

void solve(){
    for(int len = 1; len <= M; len++){
        for(int p = 0; p + len <= M; p++){
            int q = p + len;

            // 수평 먼저 잘라보고
            dpH[p][q] = horizontal(p, q);

            if (min_height[p][q] > valley[p])
                dpL[p][q] = vertical_left(p, q);

            if (min_height[p][q] > valley[q])
                dpR[p][q] = vertical_right(p, q);
        }
    }

    cout << min(dpL[0][M], dpR[0][M]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}
