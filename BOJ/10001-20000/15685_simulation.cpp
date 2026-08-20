#include <iostream>
#include <vector>
#define LINE 1
using namespace std;

int N, x, y, d, g;
int map[101][101];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};
vector<int> curve;

void init() { cin >> N; }

void generation() {
    int size = curve.size();
    for (int j = size - 1; j >= 0; j--) {
        int nd = (curve[j] + 1) % 4;
        y += dy[nd];
        x += dx[nd];
        map[y][x] = LINE;
        curve.push_back(nd);
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        // 초기화
        cin >> x >> y >> d >> g;
        curve.clear();
        map[y][x] = LINE;
        curve.push_back(d);

        // 0
        y += dy[d];
        x += dx[d];
        map[y][x] = LINE;

        // g 중첩
        for (int i = 0; i < g; i++) {
            generation();
        }
    }

    // 사각형 개수 세기
    int answer = 0;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1])
                answer++;
        }
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}