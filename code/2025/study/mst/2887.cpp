#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// 다구하면 메모리든 시간이든 뭐든 터져버림
// 어차피 한 점에서 이어질 수 있는건 가장 가까운 점
// 그럼 가장 가까운 점만 이어질 수 있나?
// 1차원은 그렇다. 어떤 점 x에서 가장 가까운 점 y대신에 다른 점이 선택 될 수 없다.
// 2차원은?
// 예를들어 0,0 1,9999 2,2 9999,1 이러려면 모든 거리를 구해야한다.
// 그런데 문제 거리가 좀 이상하다 min(|x-x|,|y-y|,|z-z|)라서 좌표별로 1차원이라 생각해도 되나.
// x,y,z별로 1차원으로 나열된 것.
// x,y,z 인접한 6개의 점이 이어질 수 있음
// pq에 들어갈 것만 6*100000*0.5 메모리도 됨  500000

// 틀렸던 여러가지 이유
// 정렬할때 index가 바뀌는 것을 고려 안함 -> index변수 추가
// 인접한 두 점만 탐색하겠다 해놓고 pushingpq에서 이중포문 쓰려함 -> 수정
// pq.pop()을 안함 -> 수정
// union_parent를 안함 -> 수정
int p[100001], N;
vector<pair<pair<int, int>, pair<int, int>>> arr;
priority_queue<pair<int, pair<int, int>>> pq;

void pushingpq() {
    for (int i = 0; i < N - 1; i++) {
        int x1 = arr[i].first.first;
        int y1 = arr[i].second.first;
        int z1 = arr[i].second.second;
        int x2 = arr[i + 1].first.first;
        int y2 = arr[i + 1].second.first;
        int z2 = arr[i + 1].second.second;

        int cost = min({abs(x1 - x2), abs(y1 - y2), abs(z1 - z2)});
        pq.push({-cost, {arr[i].first.second, arr[i + 1].first.second}});
    }
}
bool compx(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b) { return a.first.first < b.first.first; }

bool compy(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b) { return a.second.first < b.second.first; }

bool compz(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b) { return a.second.second < b.second.second; }

void init() {
    cin >> N;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        arr[i] = {{x, i}, {y, z}};
        p[i] = i;
    }
    // 세번의 정렬과 추가
    sort(arr.begin(), arr.end(), compx);
    pushingpq();
    sort(arr.begin(), arr.end(), compy);
    pushingpq();
    sort(arr.begin(), arr.end(), compz);
    pushingpq();
}

int find_parent(int x) {
    if (p[x] == x)
        return x;
    return p[x] = find_parent(p[x]);
}

void union_parent(int a, int b) {
    a = find_parent(a);
    b = find_parent(b);
    p[a] = b;
}

void solve() {
    int cnt = 0, answer = 0;
    while (cnt < N - 1) {
        int c = -pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();
        u = find_parent(u);
        v = find_parent(v);
        if (u == v)
            continue;
        union_parent(u,v);
        cnt++;
        answer += c;
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