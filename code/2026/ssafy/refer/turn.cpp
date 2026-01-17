#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int r;
    int c;
    int s;
} rotation;

bool selected[6];
int map[51][51];
int copy_map[51][51];
int N, M, K;
int answer;
vector<rotation> rot;

void init() {
    answer = 2100000000;
    // 초기화
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
    rot.clear();
    rot.resize(K);
    for (auto &a : rot) {
        int r, c, s;
        cin >> r >> c >> s;
        a = {r - 1, c - 1, s};
    }
}

void total() {
    for (int i = 0; i < N; i++) {
        int tmp = 0;
        for (int j = 0; j < M; j++) {
            tmp += copy_map[i][j];
        }
        answer = min(answer, tmp);
    }
}

void rotate(int x1, int y1, int x2, int y2) {
    int tmp = copy_map[x1][y1];

    // 오른쪽으로
    for (int i = x1; i < x2; i++) {
        copy_map[i][y1] = copy_map[i + 1][y1];
    }
    // 아래로
    for (int i = y1; i < y2; i++) {
        copy_map[x2][i] = copy_map[x2][i + 1];
    }
    // 왼쪽으로
    for (int i = x2; i > x1; i--) {
        copy_map[i][y2] = copy_map[i - 1][y2];
    }
    // 위로
    for (int i = y2; i > y1; i--) {
        copy_map[x1][i] = copy_map[x1][i - 1];
    }
    copy_map[x1][y1 + 1] = tmp;
}

void fnd(vector<int> order) {
    for (int i = 0; i < order.size(); i++) {
        rotation cur = rot[order[i]];
        for (int j = 1; j <= cur.s; j++) {
            rotate(cur.r - j, cur.c - j, cur.r + j, cur.c + j);
        }
    }
    total();
}
void dfs(int cnt, vector<int> order) {
    if (cnt == K) {
        copy(&map[0][0], &map[0][0] + (51 * 51), &copy_map[0][0]);
        fnd(order);
        return;
    }

    for (int i = 0; i < K; i++) {
        if (selected[i] == true) {
            continue;
        }

        selected[i] = true;
        order.push_back(i);

        dfs(cnt + 1, order);

        order.pop_back();
        selected[i] = false;
    }
}

int solve() {
    // 단순 구현
    vector<int> order;
    dfs(0, order);
    return answer;
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