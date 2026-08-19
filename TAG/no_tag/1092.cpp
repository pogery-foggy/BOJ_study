#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> crains, boxes;
vector<queue<int>> crain_q;
vector<bool> visit;
int N, M;

bool cmp(int a, int b) { return a > b; }

void init() {
    cin >> N;
    crains.resize(N);
    crain_q.resize(N);
    for (auto &a : crains) {
        cin >> a;
    }
    cin >> M;
    boxes.resize(M);
    visit.resize(M);
    for (int i = 0; i < M; i++) {
        visit[i] = false;
    }
    for (auto &a : boxes) {
        cin >> a;
    }
    sort(crains.begin(), crains.end(), cmp);
    sort(boxes.begin(), boxes.end(), cmp);
    int idx = 0;
    for (int j = 0; j < M; j++) {
        for (int i = idx; i < N; i++) {
            if (crains[i] >= boxes[j]) {
                crain_q[i].push(j);
            }
        }
    }
    /*for (auto a : crain_q) {

         while (!a.empty()) {
             cout << boxes[a.front()] << " ";
             a.pop();
         }
         cout << "\n";
     }*/
}

void solve() {
    if (crains[0] < boxes[0]) {
        cout << -1;
        return;
    }
    int cnt = 0;
    int time = 0;
    while (cnt < M) {
        for (int i = 0; i < N; i++) {
            while (!crain_q[i].empty() && visit[crain_q[i].front()]) {
                 crain_q[i].pop();
            }
            if (crain_q[i].empty())
                continue;
            visit[crain_q[i].front()] = true;
            crain_q[i].pop();
            cnt++;
        }
        time++;
    }
    cout << time;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}