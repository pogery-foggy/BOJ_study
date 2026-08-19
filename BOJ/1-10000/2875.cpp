#include <iostream>

using namespace std;

int N, M, K, team1, team2;

void init() { cin >> N >> M >> K; }

void solve() {

    int team = min(N / 2, M);

    int n_remain = max(0, N - 2 * team), m_remain = max(0, M - team);
    K = K - n_remain - m_remain;

    while(K>0){
        K-=3;
        team--;
    }
    cout << team;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}