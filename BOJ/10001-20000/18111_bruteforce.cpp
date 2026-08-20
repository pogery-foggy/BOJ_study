#include <iostream>

using namespace std;
int arr[501][501];

int N, M, B, answer[2];
void init() {
    cin >> N >> M >> B;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
        }
    }
    answer[0] = 2147483647;
}

void solve() {
    for (int h = 0; h <= 256; h++) {
        int b = 0, d = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int y = arr[i][j] - h;
                if (y > 0)
                    d += arr[i][j] - h;
                else if (y < 0)
                    b += h - arr[i][j];
            }
        }
        if (b <= B + d) {
            int t = d * 2 + b;
            if (answer[0] >= t) {
                answer[0] = t;
                answer[1] = h;
            }
        }
    }
    cout << answer[0] << " " << answer[1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}