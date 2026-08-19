#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int arr[100001], a_i, N, M;
long long answer;
vector<int> b_i;

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> a_i;
        arr[a_i]++;
    }
    b_i.resize(M);
    for (auto &a : b_i) {
        cin >> a;
    }
    sort(b_i.begin(), b_i.end());
    for (int i = 0; i < b_i.size(); i++)
        arr[i + 1] -= b_i[i];
}

void solve() {
    for (int i = 0; i <= 100000; i++) {
        answer += arr[i];
        if (answer > 0)
            answer = 0;
    }
    if (answer == 0)
        cout << "YES";
    else if (answer < 0)
        cout << "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}