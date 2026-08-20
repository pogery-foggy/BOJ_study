#include <iostream>
#include <set>

using namespace std;

char mode;
int k, num;
multiset<int> ms;

void init() {
    cin >> k;
    while (!ms.empty()) {
        ms.erase(ms.begin());
    }
}

void solve() {
    for (int i = 0; i < k; i++) {
        cin >> mode >> num;
        if (mode == 'I') {
            ms.insert(num);
        } else {
            if (!ms.empty() && num < 0) {
                ms.erase(ms.begin());
            } else if (!ms.empty() && num > 0) {
                auto iter = ms.end();
                ms.erase(--iter);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        init();
        solve();
        if (ms.empty())
            cout << "EMPTY"
                 << "\n";
        else {
            auto e_iter = ms.end();
            cout << *(--e_iter) << ' ' << *ms.begin() << "\n";
        }
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}