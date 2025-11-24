#include <iostream>
#define MAX_N 500
using namespace std;

int N, M, K;
int cancle[MAX_N], counter, wrong_answer;

void init() {
    cin >> N >> M >> K;
    counter = 0;
    wrong_answer = N - M;
    for (int i = 0; i < N; i++) // 초기화
        cancle[i] = 0;
    // 틀린문제 없으면 그대로 시뮬레이션
    if (!wrong_answer)
        return;

    // 거꾸로 가면서 카운터 자리에 표시하기
    for (int i = N - 1; i >= 0; i--) {
        if (++counter == K) {
            counter = 0;
            cancle[i] = 1;
            wrong_answer--;
            if (wrong_answer == 0)
                break;
        }
    }
    // 틀린문제가 남았을경우
    for (int i = 0; wrong_answer > 0; i++) {
        if (!cancle[i]) {
            wrong_answer--;
            cancle[i] = 1;
        }
    }
}
void solve() {
    int answer = 0;
    counter = 0;
    for (int i = 0; i < N; i++) {
        if (cancle[i]) {
            counter = 0;
            continue;
        }
        answer++;
        if(++counter == K) {answer *= 2; counter = 0;}
    }
    cout << answer << "\n";
}
int main(int argc, char **argv) {
    int test_case;
    int T;
    std::ios::sync_with_stdio(false);

    cin >> T;
    for (test_case = 1; test_case <= T; test_case++) {
        cout << "#" << test_case << " ";
        init();
        solve();
    }

    return 0; // 정상종료시 반드시 0을 리턴해야 합니다.
}
