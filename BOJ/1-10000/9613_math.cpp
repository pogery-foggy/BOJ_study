#include <iostream>
#include <vector>
using namespace std;

vector<int> arr;
int N;
long long answer;

void init() {
    cin >> N;
    answer = 0;
    arr.clear();
    arr.resize(N);
    for (auto &x : arr) {
        cin >> x;
    }
}

int GCD(int a, int b) {
    int maxi, mini;
    maxi = max(a, b);
    mini = min(a, b);
    while (maxi % mini != 0) {
        maxi -= mini;
        if (maxi >= mini) {
            continue;
        } else {
            int temp = maxi;
            maxi = mini;
            mini = temp;
        }
    }
    return mini;
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            answer += GCD(arr[i], arr[j]);
        }
    }
    cout << answer << "\n";
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
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}