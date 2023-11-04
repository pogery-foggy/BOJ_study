#include <iostream>

using namespace std;
long long map[101][101];
long long answer[101][101];
int N;
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
        }
    }
    answer[1][1] = 1;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            long long jump = map[i][j];
            if (jump == 0) {
                cout << answer[N][N];
                return;
            }
            if (jump + i <= N)
                answer[i + jump][j] += answer[i][j];
            if (jump + j <= N)
                answer[i][j + jump] += answer[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}