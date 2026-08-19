#include <iostream>
#define MAX_N 100
using namespace std;
int map[MAX_N][MAX_N];
int is_used[MAX_N][MAX_N];
int N, L;
void init() {
    cin >> N >> L;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
}

void solve() {
    int total = 0;
    for (int i = 0; i < N; i++) {
        bool flag = true;
        int ago = map[i][0];
        int cnt = 1;
        for (int j = 1; j < N; j++) {
            if (map[i][j] != map[i][j - 1]) {
                if (map[i][j] - map[i][j - 1] > 1) { // 갈곳이 두칸이상 높다면
                    flag = false;
                    break;
                } else if (map[i][j] - map[i][j - 1] == 1) {
                    if (cnt < L) {
                        flag = false;
                        break;
                    } else {
                        for (int k = j - 1; k > j - 1 - L; k--) {
                            if (is_used[i][k]) {
                                flag = false;
                                break;
                            } else {
                                is_used[i][k] = true;
                            }
                        }
                    }
                }
                cnt = 1;
            } else {
                cnt++;
            }
        }
        // 거꾸로 한번 더
        cnt = 1;
        ago = map[i][N - 1];
        for (int j = N - 2; j >= 0; j--) {
            if (map[i][j] != map[i][j + 1]) {
                if (map[i][j] - map[i][j + 1] > 1) { // 갈곳이 두칸이상 높다면
                    flag = false;
                    break;
                } else if (map[i][j] - map[i][j + 1] == 1) {
                    if (cnt < L) {
                        flag = false;
                        break;
                    } else {
                        for (int k = j + 1; k < j + 1 + L; k++) {
                            if (is_used[i][k]) {
                                flag = false;
                                break;
                            } else {
                                is_used[i][k] = true;
                            }
                        }
                    }
                }
                cnt = 1;
            } else {
                cnt++;
            }
        }
        if (flag) {
            total++;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            is_used[i][j] = false;
        }
    }
    for (int j = 0; j < N; j++) {
        bool flag = true;
        int ago = map[0][j];
        int cnt = 1;
        for (int i = 1; i < N; i++) {
            if (map[i][j] != map[i - 1][j]) {
                if (map[i][j] - map[i - 1][j] > 1) { // 갈곳이 두칸이상 높다면
                    flag = false;
                    break;
                } else if (map[i][j] - map[i - 1][j] == 1) {
                    if (cnt < L) {
                        flag = false;
                        break;
                    } else {
                        for (int k = i - 1; k > i - 1 - L; k--) {
                            if (is_used[k][j]) {
                                flag = false;
                                break;
                            } else {
                                is_used[k][j] = true;
                            }
                        }
                    }
                }
                cnt = 1;
            } else {
                cnt++;
            }
        }
        // 거꾸로 한번 더
        ago = map[N - 1][j];
        cnt = 1;
        for (int i = N - 2; i >= 0; i--) {
            if (map[i][j] != map[i + 1][j]) {
                if (map[i][j] - map[i + 1][j] > 1) { // 갈곳이 두칸이상 높다면
                    flag = false;
                    break;
                } else if (map[i][j] - map[i + 1][j] == 1) {
                    if (cnt < L) {
                        flag = false;
                        break;
                    } else {
                        for (int k = i + 1; k < i + 1 + L; k++) {
                            if (is_used[k][j]) {
                                flag = false;
                                break;
                            } else {
                                is_used[k][j] = true;
                            }
                        }
                    }
                }
                cnt = 1;
            } else {
                cnt++;
            }
        }
        if (flag) {
            total++;
        }
    }
    cout << total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}