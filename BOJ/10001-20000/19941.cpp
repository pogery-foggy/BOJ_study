#include <iostream>
#include <string>
using namespace std;
bool is_visit[20000];
int n, k;
string s;

void init() {
    cin >> n >> k;
    cin >> s;
}

void solve() {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'P') {
            for (int j = max(i - k, 0); j < min(i + k + 1, n); j++) {
                if (!is_visit[j] && s[j] == 'H') {
                    cnt++;
                    is_visit[j] = true;
                    break;
                }
            }
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