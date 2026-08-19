#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> idx;
void init() {
    cin >> N;
    idx.clear();
}

void solve() {
    for (int i = 0; i < 32; i++) {
        if (N & 1 << i)
            idx.push_back(i);
    }

    for (auto a : idx) {
        cout << a << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}