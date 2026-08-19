#include <algorithm>
#include <iostream>
using namespace std;

int arr[3];

void init() {
    cin >> arr[0] >> arr[1] >> arr[2];
    sort(arr, arr + 3);
}

void solve() {
    int answer = arr[0] + arr[1];
    if (arr[2] >= arr[0] + arr[1])
        answer += arr[0] + arr[1] - 1;
    else
        answer += arr[2];
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}