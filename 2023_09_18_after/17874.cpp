#include <algorithm>
#include <iostream>
using namespace std;
int N, H, V;
void init() { cin >> N >> H >> V; }

void solve() {
    long long answer = max({H * V, H * (N - V), (N - H) * V, (N - H) * (N - V)});
    cout << answer * 4;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}