#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int C, N;
vector<int> chick;
vector<pair<int, int>> cow;
priority_queue<int, vector<int>, greater<int>> pq;

// 자신이 포함될 수 없는 곳 전 까지 me<s 전 까지
// 그러면 그들 중 e가 가장 작은 것이 항상 올바른 답이란 것을 증명 할 수 있는가.
// 만약 s < e < me 인 상태에서 pq에 추가 안했을 경우
// 항상 다음 me'이 s < me' < e는 될 수 없다?
// me < me'가 보장되니까 불가능
void init() {
    cin >> C >> N;
    chick.resize(C);
    cow.resize(N);
    for (auto &a : chick) {
        cin >> a;
    }
    for (int i = 0; i < N; i++) {
        int s, e;
        cin >> s >> e;
        cow[i] = {s, e};
    }

    sort(chick.begin(), chick.end());
    sort(cow.begin(), cow.end());
}

void solve() {
    int chick_num = 0;
    int cow_num = 0;
    int cnt = 0;
    while (chick_num < C) {
        while (!pq.empty() && chick[chick_num] > pq.top())
            pq.pop();
        while (cow_num < N) {
            if (chick[chick_num] < cow[cow_num].first) { // me < s -> break;
                break;
            } else { // s < me  <= e
                if (chick[chick_num] <= cow[cow_num].second)
                    pq.push(cow[cow_num].second);
                cow_num++;
            }
        }
        if (!pq.empty()) {
            cnt++;
            pq.pop();
        }
        chick_num++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}