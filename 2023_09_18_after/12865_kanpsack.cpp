#include <iostream>
#define W 0
#define V 1
using namespace std;

int N, K;
int knapsack[101][100001];
int item[101][2]; // 무게 가치

void init() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> item[i][W] >> item[i][V];
    }
}

void solve() {
    for (int i = 1; i <= N; i++) {
        for (int w = 1; w <= K; w++) {
            if (item[i][W] <= w)
                knapsack[i][w] = max(knapsack[i - 1][w], knapsack[i - 1][w - item[i][W]] + item[i][V]);
            else
                knapsack[i][w] = knapsack[i - 1][w];
        }
    }
    cout << knapsack[N][K];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}