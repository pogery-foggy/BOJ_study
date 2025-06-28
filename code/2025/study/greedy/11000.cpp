#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N;
vector<pair<int, int>> schedule;
priority_queue<int, vector<int>, greater<int>> end_time;

void init() {
    cin >> N;
    schedule.resize(N);
    for (int i = 0; i < N; i++) {
        int s, e;
        cin >> s >> e;
        schedule[i] = {s, e};
    }
    sort(schedule.begin(), schedule.end());
}

void solve() {
    end_time.push(schedule[0].second);
    int sz = 1;
    for (int i = 1; i < N; i++) {
        int start_time = schedule[i].first;
        bool fnd = false;
        for (int room = 0; room < sz; room++) {
            if (end_time.top() <= start_time) {
                end_time.pop();
            }
            end_time.push(schedule[i].second);
        }
    }
    cout << end_time.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}