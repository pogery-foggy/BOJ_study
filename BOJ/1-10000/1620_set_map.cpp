#include <iostream>
#include <map>
#include <string>
#define MAX_N 100001
using namespace std;

int N, M;
string answer[MAX_N];
map<string, int> dogam;

void init() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> answer[i];
        dogam.insert({answer[i], i});
    }
}

void solve() {
    string user_in;
    for (int i = 0; i < M; i++) {
        cin >> user_in;
        if ('0' <= user_in[0] && '9' >= user_in[0]) {
            cout << answer[stoi(user_in)] << "\n";
        } else
            cout << dogam[user_in] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}