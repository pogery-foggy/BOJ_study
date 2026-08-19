#include <iostream>
#define W 0
#define V 1

using namespace std;

int N, K;
int knapsack[1001][10001];
int item[1001][2];
void init() {
    cin >> N >> K;
    for (int i = 1; i <= K; i++) {
        cin >> item[i][V] >> item[i][W];
    }
}
// i가 그저 물건의 번호라는 것을 잊지 않으면 쉬움
void solve() {
    for (int i = 1; i <= K; i++) {
        for (int w = 1; w <= N; w++) {
            if (item[i][W] <= w)
                knapsack[i][w] = max(knapsack[i - 1][w], knapsack[i - 1][w - item[i][W]] + item[i][V]);
            else
                knapsack[i][w] = knapsack[i - 1][w];
        }
    }
    cout << knapsack[K][N];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}