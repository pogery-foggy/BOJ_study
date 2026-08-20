#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
ll mini, maxi;
bool prime[1000001];
int answer = 0;

void init() {
    cin >> mini >> maxi;
}

void solve() {
    ll limit = sqrtl(maxi) + 1;

    for (ll i = 2; i <= limit; i++) {
        ll cur = i * i; 
        ll x = (mini + cur - 1) / cur;
        ll s = x * cur;
        for (ll j = s; j <= maxi; j += cur) {
            prime[j - mini] = 1;
        }
    }

    for (int i = 0; i < maxi - mini + 1; i++) {
        if (!prime[i]) answer++;
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}