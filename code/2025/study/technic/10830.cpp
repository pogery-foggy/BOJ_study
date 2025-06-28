#include <iostream>
#include <vector>
#define DIV 1000
using namespace std;
typedef long long ll;
ll N, B;
ll answer[5][5], cur[5][5];

void mul(ll a[5][5], ll b[5][5]) {
    // a에다가 b를 곱하는 함수
    ll temp[5][5];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            temp[i][j] = 0;
            for (int k = 0; k < N; k++)
                temp[i][j] = (temp[i][j] + a[i][k] * b[k][j]) % DIV;
        }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = temp[i][j];
}

void init() {
    cin >> N >> B;
    for (int i = 0; i < N; i++) {
        answer[i][i] = 1;
        for (int j = 0; j < N; j++)
            cin >> cur[i][j];
    }
}

void solve() {
    // cur ^2 and if B&1 ans *= cur
    while (B > 0) {
        if (B & 1)
            mul(answer, cur); // ans *= cur
        mul(cur, cur);        // cur ^ 2
        B >>= 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << answer[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}