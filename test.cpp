#include <iostream>
#include <vector>
using namespace std;

long long N, R, m, fnd, answer;

void init() { cin >> N >> R; }

void solve() {
    fnd = N - R;
    for (long long i = 1; i * i <= fnd; i++) {
        if (fnd % i == 0) {
            if (i > R)
                answer += i;
            if (i * i != fnd && (fnd / i) > R)
                answer += fnd / i;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << answer;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}