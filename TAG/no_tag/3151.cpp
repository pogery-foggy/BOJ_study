#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
vector<ll> m, p;
ll num_cnt[20002], N; // -10000~10000, 10000-a,a+10000, zero_cnt == cnt[10000];
bool is_visit[20002];

void init() {
    // zero_cnt C 3;            1
    // zero_cnt * (a == -c);    N
    // a + b == -c;
    // -a == b + c;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        if (a < 0)
            m.push_back(-a);
        else if (a > 0)
            p.push_back(a);
        num_cnt[a + 10000]++;
    }
    sort(m.begin(), m.end());
    sort(p.begin(), p.end());
}

void solve() {
    ll answer = 0;
    ll zero_cnt = num_cnt[10000];

    // zero_cnt C 3;
    if (zero_cnt > 2) {
        answer += zero_cnt * (zero_cnt - 1) * (zero_cnt - 2) / 6;
    }

    // zero_cnt * (a==-c)
    if (zero_cnt > 0) {
        ll cnt = 0;
        for (int i = 1; i <= 10000; i++) {
            if (num_cnt[10000 - i] > 0 && num_cnt[i + 10000] > 0) {
                cnt += num_cnt[10000 - i] * num_cnt[i + 10000];
            }
        }
        answer += cnt * zero_cnt;
    }

    // a + b == -c;
    for (int i = 0; i < m.size(); i += 1 * num_cnt[10000 - m[i]]) {
        int c = m[i];
        int l = 0, r = p.size() - 1;
        while (l < r) {
            int a = p[l];
            int b = p[r];
            if (a + a == c || b + b == c) {
                if (a + a == c) {
                    answer += num_cnt[10000 - c] * num_cnt[a + 10000] * (num_cnt[a + 10000] - 1) / 2;
                    l += 1 * num_cnt[a + 10000];
                } else {
                    answer += num_cnt[10000 - c] * num_cnt[b + 10000] * (num_cnt[b + 10000] - 1) / 2;
                    r -= 1 * num_cnt[b + 10000];
                }
            }
            if (a == b)
                break; // 중앙에서 만났는데 같은 값일경우
            if (a + b == c) {
                answer += num_cnt[10000 - c] * num_cnt[a + 10000] * num_cnt[b + 10000];
                l += 1 * num_cnt[a + 10000];
                r -= 1 * num_cnt[b + 10000];
            } else if (a + b > c) {
                r -= 1 * num_cnt[b + 10000];
            } else
                l += 1 * num_cnt[a + 10000];
        }
    }

    // -a == l + r;
    for (int i = 0; i < p.size(); i += 1 * num_cnt[p[i] + 10000]) {
        int c = p[i];
        int l = 0, r = m.size() - 1;
        while (l < r) {
            int a = m[l];
            int b = m[r];
            if (a + a == c || b + b == c) {
                if (a + a == c) {
                    answer += num_cnt[c + 10000] * num_cnt[10000 - a] * (num_cnt[10000 - a] - 1) / 2;
                    l += 1 * num_cnt[10000 - a];
                } else {
                    answer += num_cnt[c + 10000] * num_cnt[10000 - b] * (num_cnt[10000 - b] - 1) / 2;
                    r -= 1 * num_cnt[10000 - b];
                }
            }
            if (a == b)
                break; // 중앙에서 만났는데 같은 값일경우
            if (a + b == c) {
                answer += num_cnt[c + 10000] * num_cnt[10000 - a] * num_cnt[10000 - b];
                l += 1 * num_cnt[10000 - a];
                r -= 1 * num_cnt[10000 - b];
            } else if (a + b > c) {
                r -= 1 * num_cnt[10000 - b];
            } else
                l += 1 * num_cnt[10000 - a];
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