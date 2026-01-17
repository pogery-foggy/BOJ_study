#include <algorithm>
#include <iostream>
using namespace std;
int N, M;
int arr[20][2];

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> arr[i][0];
    for (int i = 0; i < M; i++)
        cin >> arr[i][1];
}

int solve() {
    int answer = -2100000000;
    int flag = 0;
    if (N > M) {
        swap(N, M);
        flag = 1;
    }
    for (int i = 0; i <= M - N; i++) {
        int total = 0;
        for (int j = 0; j < N; j++) {
            total += arr[i + j][1 ^ flag] * arr[j][0 ^ flag];
        }
        answer = max(answer, total);
    }
    return answer;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 1; testcase <= T; testcase++) {
        init();
        cout << "#" << testcase << " " << solve() << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}