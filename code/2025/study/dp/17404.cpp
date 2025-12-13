#include <iostream>
#include <algorithm>
#define MAX_N 1001
#define INF 2100000000
using namespace std;

int R[MAX_N][3],B[MAX_N][3],G[MAX_N][3];
int cost[MAX_N][3];
int N;
void init() {
    cin >> N;
    for(int i = 1; i <= N; i++){
        for(int j = 0; j < 3; j++){
            cin >> cost[i][j];
        }
    }
    R[1][0] = cost[1][0];
    B[1][1] = cost[1][1];
    G[1][2] = cost[1][2];
    R[1][1] = R[1][2] = B[1][0] = B[1][2] = G[1][0] = G[1][1] = INF;
}

void solve() {
    for(int i = 2; i <= N; i++){
        for(int j = 0; j < 3; j++){
            R[i][j] = cost[i][j] + min(R[i-1][(j+1)%3], R[i-1][(j+2)%3]);
            B[i][j] = cost[i][j] + min(B[i-1][(j+1)%3], B[i-1][(j+2)%3]);
            G[i][j] = cost[i][j] + min(G[i-1][(j+1)%3], G[i-1][(j+2)%3]);
        }
    }
    int a = min(R[N][1], R[N][2]);
    int b = min(B[N][0], B[N][2]);
    int c = min(G[N][0], G[N][1]);
    a = min(a, b);
    cout << min(a, c);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}