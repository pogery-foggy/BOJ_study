#include <algorithm>
#include <iostream>
#include <set>
#include <string>
using namespace std;

set<string> str, answer;
string user_in;
int cnt, N, M;

void init() {
    cnt = 0;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> user_in;
        str.insert(user_in);
    }
}

void solve() {
    for (int i = 0; i < M; i++) {
        cin >> user_in;
        auto fnd = str.find(user_in);
        if (fnd != str.end()) {
            cnt++;
            answer.insert(*fnd);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << cnt << "\n";
    for (auto a : answer)
        cout << a << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}