#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int N;
int arr[100000];
long long answer;
void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + N);
}

int not_zero(int x) {
    if (x < 0)
        x = 0;
    return x;
}

void solve() {
    for (int i = 0; i < N; i++) {
        answer += not_zero(arr[i] - (N - i - 1));
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