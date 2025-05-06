#include <algorithm>
#include <iostream>
using namespace std;

int map[9][50];
int N;
// 몇번 타자인지
int order[9];
bool selected[9];
int maxi = -1;
void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> map[j][i];
        }
    }
    order[3] = 0;
}

void simulate() {
    int taja = 0;
    int score = 0;
    for (int i = 0; i < N; i++) {
        int out = 0;
        int base[4]; // 1 2 3 home
        base[0] = base[1] = base[2] = base[3] = 0;
        while (out < 3) {
            int cur = order[taja];
            // map[선수][이닝]
            switch (map[cur][i]) {
            case 0:
                out++;
                break;
            case 1:
                base[3] += base[2];
                base[2] = base[1];
                base[1] = base[0];
                base[0] = 1;
                break;
            case 2:
                base[3] += base[2] + base[1];
                base[2] = base[0];
                base[1] = 1;
                base[0] = 0;
                break;
            case 3:
                base[3] += base[2] + base[1] + base[0];
                base[2] = 1;
                base[1] = 0;
                base[0] = 0;
                break;
            case 4:
                base[3] += base[2] + base[1] + base[0] + 1;
                base[2] = 0;
                base[1] = 0;
                base[0] = 0;
                break;
            }
            taja = (taja + 1) % 9;
        }
        score += base[3];
    }
    maxi = max(maxi, score);
}

// 1번선수(0)는 배제
void tasoon(int cnt) {
    // 4번타자는 1번 선수로 고정
    if (cnt == 3)
        cnt++;

    if (cnt == 9) {
        simulate();
        return;
    }
    for (int i = 1; i < 9; i++) {
        if (selected[i])
            continue;
        order[cnt] = i;
        selected[i] = true;
        tasoon(cnt + 1);
        selected[i] = false;
    }
}

void solve() {
    tasoon(0);
    cout << maxi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}