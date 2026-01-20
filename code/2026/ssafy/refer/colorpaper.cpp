#include <algorithm>
#include <iostream>
#include <vector>
#define N 10
using namespace std;

int map[N][N];
int cnt_1, answer;
// int paper[25] = {5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1};
int left_paper[6]; // 각 색종이 남은 개수

void init() {
    cnt_1 = 0;
    answer = 2100000000;
    for (int i = 1; i <= 5; i++)
        left_paper[i] = 5;
    // 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j])
                cnt_1++;
        }
    }
}

bool is_valid(int y, int x) {
    if (y < 0 || N <= y)
        return false;
    if (x < 0 || N <= x)
        return false;
    return true;
}

bool can_putting(int y, int x, int area) {
    int flag = true;
    for (int i = y; i < y + area; i++) {
        for (int j = x; j < x + area; j++) {
            if (map[i][j] == 0)
                flag = false;
        }
    }
    return flag;
}

void dig(int y, int x, int area) {
    for (int i = y; i < y + area; i++) {
        for (int j = x; j < x + area; j++) {
            map[i][j] = 0;
        }
    }
}
void recover(int y, int x, int area) {
    for (int i = y; i < y + area; i++) {
        for (int j = x; j < x + area; j++) {
            map[i][j] = 1;
        }
    }
}

void dfs(int cnt) {
    if (cnt >= answer)
        return; // 이미 답을 넘으면

    int sy = -1, sx = -1;
    for (int i = 0; i < N; i++) {
        bool one = false;
        for (int j = 0; j < N; j++) {
            if (map[i][j]) {
                sy = i;
                sx = j;
                one = true;
                break;
            }
        }
        if (one)
            break;
    }

    // 만약 1이 없으면 -1,-1
    if (sy == -1 && sx == -1) {
        answer = min(cnt, answer);
        return;
    }

    // 바꿔서 가장 왼쪽 위에 있는 칸만 5 4 3 2 1 체크
    // 이번 depth에서 쓸 색종이 크기

    // 사이즈별로 개수 세가지고 시도.
    for (int sz = 5; sz >= 1; sz--) {
        if (!left_paper[sz])
            continue;
        if (sy + sz > N || sx + sz > N)
            continue;

        if (!can_putting(sy, sx, sz))
            continue;
        left_paper[sz]--;
        dig(sy, sx, sz);
        dfs(cnt + 1);
        left_paper[sz]++;
        recover(sy, sx, sz);
    }
}

int solve() {
    if (cnt_1 < 4)
        return cnt_1;
    dfs(0);
    if (answer == 2100000000)
        return -1;
    else
        return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    cout << solve();

    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}
/*25장의 색종이를 선택하거나 선택하지 않거나.
배열로 {5,5,5,5,5,4,4,4,4,4,3,3,3,3,3,2,2,2,2,2,1,1,1,1,1} 넣어놓고 인덱스로 접근
10x10의 배열을 탐색하면서 1이면 현재 들고있는 색종이가 들어갈 수 있는지 확인
색종이가 들어갈 수 있다면 아예 덮기
total += cur*cur; 덮기 dfs(index+1, total) 복구하기 total-= cur*cur
/5*5 하면 다음크기의 색종이로 넘어갈 수 있음. 쓸데가 있나?

순수하게 모든 색종이가 5크기고 맵의 모든 칸에서 탐색한다 할때 100*25*25 = 62500*25 = 약 150만 시간 충분
무조건 왼쪽상단의 칸부터 넣는게, 다른 칸에 넣는 것보다 가장 효율적인가?
예외가 있나? 증명이 궁금하다



최종 : 색종이 개수 배열만들고  개수 다 떨어지면 못붙이게,
그리고 현재 기준 가장 왼쪽 상단에 붙이면 됨.
만약 최적의 자리가 아니라고 한다면 왼쪽 또는 위로 더 1이 있다는 거고 그럼 첫 선택이 왼쪽 상단이 아니게됨. 모순
그리고 칸 없애고, 개수 없애고 dfs후복구
들어간 테크닉은 만약 최상단 좌표가 -1,-1이면 1이 없는 것이므로 끝
그리고 cnt가 이미 answer을 넘어섰으면 더 탐색할 필요가 없음
x+area로 범위까지만
*/