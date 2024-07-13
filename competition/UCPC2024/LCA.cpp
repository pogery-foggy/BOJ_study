#include <iostream>
#include <queue>
#include <vector>
#define MAX_SIZE 100001
using namespace std;

// 나중에 벡터가 아니라 노드로도 구현해 볼것.

int parrent[MAX_SIZE][17], depth[MAX_SIZE]; // 나중에 합칠 것
vector<int> child[MAX_SIZE];
bool is_visit[MAX_SIZE];
int N;
long long answer;
queue<int> Q;

void dp() { // 나중에 한번더 보자 LCA dp의 기초급
    for (int j = 1; j < 17; j++) {
        for (int i = 1; i <= N; i++) {
            parrent[i][j] = parrent[parrent[i][j - 1]][j - 1];
        }
    }
}

int LCA(int a, int b) {
    if (depth[a] < depth[b])
        swap(a, b);
    int diff = depth[a] - depth[b];
    for (int i = 0; diff; i++) {
        if (diff & 1)
            a = parrent[a][i];
        diff >>= 1;
    }
    if (a == b)
        return a;
    /* 둘 사이의 부모조상 거리를 좁혀나가는 것.
    만약 부모조상까지 거리가 6일때 8이면 같으니까 다음루트
    4면 다르니까 각 노드의 거리를 4빼서 좁히고
    2를 빼면 같으니까 다시 다음루트
    1을 빼면 다르니까 저장
    결국 남은 것의 부모노트가 찾고자 하는 조상노트가 됨*/
    for (int i = 16; i >= 0; i--)
        if (parrent[a][i] != parrent[b][i]) {
            a = parrent[a][i];
            b = parrent[b][i];
        }
    return parrent[a][0];
}

int dist(int node1, int node2) {
    int lca = LCA(node1, node2);
    int distance = depth[node1] + depth[node2] - (2 * depth[lca]);
    return distance;
}

void bfs() {
    for (auto i : child[1])
        Q.push(i);
    int cur, before = 1;
    while (!Q.empty()) {
        cur = Q.front();
        Q.pop();
        is_visit[cur] = true;

        answer += dist(before, cur);
        before = cur;
        for (auto i : child[cur])
            if (!is_visit[i])
                Q.push(i);
    }
}

void init() {
    cin >> N;
    answer = 0;
    depth[1] = 0;
    parrent[1][0] = 0;
    for (int i = 1; i <= N; i++) {
        is_visit[i] = false;
        child[i].clear();
    }
    int user_in;
    for (int children = 2; children <= N; children++) {
        cin >> user_in;
        depth[children] = depth[user_in] + 1;
        parrent[children][0] = user_in;
        child[user_in].push_back(children);
    }
}

void solve() {
    dp();
    bfs();
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        init();
        solve();
        cout << "#" << test_case << " " << answer << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}