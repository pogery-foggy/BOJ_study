#include <iostream>

using namespace std;

int arr[301][301];
int N, M;
int prefix_sum[301][301];

void init_arr(int s_x, int e_x, int s_y, int e_y) {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            prefix_sum[i][j] = prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1] + arr[i][j];
        }
    }
}

void init() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> arr[i][j];
        }
    }
    init_arr(1, N, 1, M);
}

int print_dist(int s_x, int s_y, int e_x, int e_y) {
    return prefix_sum[e_x][e_y] - prefix_sum[e_x][s_y - 1] - prefix_sum[s_x - 1][e_y] + prefix_sum[s_x - 1][s_y - 1];
}

void solve() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int s_x, e_x, s_y, e_y;
        cin >> s_x >> s_y >> e_x >> e_y;
        cout << print_dist(s_x, s_y, e_x, e_y) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}