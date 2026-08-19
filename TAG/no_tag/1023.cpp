#include <iostream>
#include <string>
#define MAX_N 54
using namespace std;
typedef long long ll;

int N;
ll K;
ll dp[MAX_N][MAX_N];   // i open_cnt
ll pow2[MAX_N];         // 2^i
string answer;
    
void init() {
    cin >> N >> K;
    pow2[0] = 1;
    for (int i = 1; i <= N; i++) {
        pow2[i] = pow2[i - 1] * 2;
    }

    dp[N][0] = 1;
    for (int i = N - 1; i >= 0; i--) {
        for (int open = 0; open <= N; open++) {
            ll v = 0;
            if (open + 1 <= N) {
                v += dp[i + 1][open + 1];
            }
            if (open > 0) {
                v += dp[i + 1][open - 1];
            }
            dp[i][open] = v;
        }
    }

    answer.reserve(N);
}

void solve() {
    if (N % 2 == 1) {
        if (K >= pow2[N]) {
            cout << -1;
            return;
        }
        string answer;
        answer.reserve(N);
        for (int i = N - 1; i >= 0; i--) {
            answer.push_back(((K >> i) & 1LL) ? ')' : '(');
        }
        cout << answer;
        return;
    }

    ll total = pow2[N] - dp[0][0];
    if (K >= total) {
        cout << -1;
        return;
    }

    int open = 0;
    bool correct = false; 
    for (int i = 0; i < N; i++) {
        int remain = N - i - 1;
        ll cnt;
        if (correct) {
            cnt = pow2[remain];
        } 
        else {
            cnt = pow2[remain] - dp[i + 1][open + 1];
        }

        if (K < cnt) {
            answer.push_back('(');
            if (!correct) open++;
        } 
        else {
            K -= cnt;
            answer.push_back(')');
            if (!correct) {
                open--;
                if (open < 0) {
                    correct = true;
                    open = 0;
                }
            }
        }
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
