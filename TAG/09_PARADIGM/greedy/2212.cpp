#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> v;
vector<int> dist;

int N, K;
bool cmp(int a, int b) {
    return a > b;
}
void init() {
    cin >> N >> K;
    v.resize(N);
    for (auto& a : v) {
        cin >> a;
    }
    sort(v.begin(), v.end());
    dist.resize(N - 1);
    for (int i = 0; i < dist.size(); i++) {
        dist[i] = v[i + 1] - v[i];
    }
    sort(dist.begin(), dist.end(), cmp);
}

void solve() {
    long long sum = 0;
    for (int i = K - 1; i < dist.size(); i++) {
        sum += dist[i];
    }
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}