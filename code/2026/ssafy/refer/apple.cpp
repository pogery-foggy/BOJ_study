#include <algorithm>
#include <iostream>
#include <vector>
#define U 1
#define M 2
#define D 3
using namespace std;
typedef pair<int, pair<int, int>> piii;

int N;
vector<piii> apple;
void init() {
    cin >> N;
    apple.clear();
    apple.push_back({0, {0, 0}});
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int a;
            cin >> a;
            if (a)
                apple.push_back({a, {i, j}});
        }
    }
    sort(apple.begin(), apple.end());
}

// 왼쪽에 있을경우 cnt + 3; d + 3;
// 오른쪽에 있을경우 위 +1; d+1;
//                 중앙 +2; d+2;
//                 아래 +2; d+2;
// 가운데에 있을경우 아래 + 3; d+3;

void lefting(int &direction, int &cnt) {
    direction = (direction + 3) % 4;
    cnt = cnt + 3;
}

void righting(int &direction, int &cnt, int umd) {
    switch (umd) {
    case U:
        direction = (direction + 1) % 4;
        cnt = cnt + 1;
        break;
    case M:
        direction = (direction + 1) % 4;
        cnt = cnt + 1;
        break;
    case D:
        direction = (direction + 2) % 4;
        cnt = cnt + 2;
    }
}

void midding(int &direction, int &cnt, int umd) {
    if (umd == D) {
        direction = (direction + 3) % 4;
        cnt = cnt + 3;
    }
}

int solve() {
    // d
    // 위  왼쪽    -j  가운데뒤 +i
    //     오른쪽  +j  위  -i
    //                 중 ==i
    //                 아래+i
    // 오  왼쪽    -i  가운데뒤 -j
    //     오른쪽  +i  위  +j
    //                 중 ==j
    //                 아래-j
    // 아  왼쪽    +j  가운데뒤 -i
    //     오른쪽  -j  위  +i
    //                 중 ==i
    //                 아래-i
    // 왼  왼쪽    +i  가운데뒤 +j
    //     오른쪽  -i  위  -j
    //                 중 ==i
    //                 아래+j

    int d = 1; // up=0, right=1, down=2, left=3;
    int cnt = 0;
    for (int i = 0; i < apple.size() - 1; i++) {
        int pi = apple[i].second.first;
        int pj = apple[i].second.second;
        int ni = apple[i + 1].second.first;
        int nj = apple[i + 1].second.second;
        switch (d) {
        case 0: // up
            if (pj == nj) {
                midding(d, cnt, (pi < ni) ? D : 0);
            } else if (pj < nj) {
                if (pi > ni)
                    righting(d, cnt, U);
                else if (pi == ni)
                    righting(d, cnt, M);
                else
                    righting(d, cnt, D);
            } else {
                lefting(d, cnt);
            }
            break;
        case 1: // right
            if (pi == ni) {
                midding(d, cnt, (pi > ni) ? D : 0);
            } else if (pi < ni) {
                if (pj < nj)
                    righting(d, cnt, U);
                else if (pj == nj)
                    righting(d, cnt, M);
                else
                    righting(d, cnt, D);
            } else {
                lefting(d, cnt);
            }
            break;
        case 2: // down
            if (pj == nj) {
                midding(d, cnt, (pi > ni) ? D : 0);
            } else if (pj > nj) {
                if (pi < ni)
                    righting(d, cnt, U);
                else if (pi == ni)
                    righting(d, cnt, M);
                else
                    righting(d, cnt, D);
            } else {
                lefting(d, cnt);
            }
            break;
        case 3: // left
            if (pi == ni) {
                midding(d, cnt, (pi > ni) ? D : 0);
            } else if (pi > ni) {
                if (pj > nj)
                    righting(d, cnt, U);
                else if (pj == nj)
                    righting(d, cnt, M);
                else
                    righting(d, cnt, D);
            } else {
                lefting(d, cnt);
            }
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        cout << "#" << testcase + 1 << " " << solve() << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}