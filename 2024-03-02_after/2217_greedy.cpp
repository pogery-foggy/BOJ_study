#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> rope;
int maxi;

bool cmp(int a, int b) { return a > b; }
void init() {
    cin >> N;
    rope.resize(N);
    for (auto &a : rope) {
        cin >> a;
    }
    sort(rope.begin(), rope.end(), cmp);
    maxi = rope[0];
}

void solve() {
    for (int i = 0; i < N; i++) {
        int cur = rope[i] * (i + 1);
        maxi = maxi > cur ? maxi : cur;
    }
    cout << maxi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}