#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int N, s, e;
vector<pair<int, int>> room;

void init() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> s >> e;
        room.push_back({e, s});
    }

    sort(room.begin(), room.end());
}

void solve() {

    int time = room[0].first;
    int cnt = 1;
    for (int i = 1; i < N; i++) {
        if (time <= room[i].second) {
            cnt++;
            time = room[i].first;
        }
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