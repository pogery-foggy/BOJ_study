#include <iostream>
#define MAX_N 16
using namespace std;

int arr[MAX_N][MAX_N][2]; // 0 은 X 1은 O를 지나침
int N, M, K, ey, ex;
void init() {
    cin >> N >> M >> K;
    ey = K / M + 1;
    ex = K % M;
    if (ex == 0) {
        ex += M;
        ey -= 1;
    }
    arr[1][0][0] = 1; // 1 1 0 을 1로 해야 하지만 그러면 O위치 + 1 1 로 시작해야하기 때문에
}

void solve() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            arr[i][j][0] = arr[i - 1][j][0] + arr[i][j - 1][0];
            arr[i][j][1] = arr[i - 1][j][1] + arr[i][j - 1][1];
            if (i == ey && j == ex) {
                arr[i][j][1] = arr[i - 1][j][0] + arr[i][j - 1][0];
            }
        }
    }
    if (!K)
        cout << arr[N][M][0];
    else
        cout << arr[N][M][1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}