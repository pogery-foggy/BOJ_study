#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int N, cnt, order = 0;
map<string, int> m;
bool cur[1002];

void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        string s;
        cin >> s;
        m[s] = i;
    }
}

void solve() {
    for (int i = 1; i <= N; i++) {
        string s;
        cin >> s;
        cur[m[s]] = true;
        while (cur[order + 1]) {
            order++;
        }
        if (order < m[s])
            cnt++;
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