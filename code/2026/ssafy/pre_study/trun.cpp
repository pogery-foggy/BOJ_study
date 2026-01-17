#include <iostream>
#define MAX_N 7
using namespace std;

int N;
int map[MAX_N][MAX_N];

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
}

void solve() {
    // 혹시라도 내 코드를 볼 분들을 위해
    // 내가 배열을 바라보는 방향을 조종할 수 있다면 따로 움직이지 않아도 됩니다.
    // i,j가 서로 뒤집혀있는 것은 for(j)for(i)로 짠 뒤 i와 j를 스위칭 한겁니다.
    // 왼쪽 아래시작, 위를 바라보기
    // 오른쪽 아래시작, 왼쪽을 바라보기
    // 오른쪽 위시작, 아래를 바라보기
    for (int i = 0; i < N; i++) {
        for (int j = N - 1; j >= 0; j--) {
            cout << map[j][i];
        }
        cout << " ";
        for (int j = N - 1; j >= 0; j--) {
            cout << map[N - i - 1][j];
        }
        cout << " ";
        for (int j = 0; j < N; j++) {
            cout << map[j][N - i - 1];
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 1; testcase <= T; testcase++) {
        init();
        cout << "#" << testcase << "\n";
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}