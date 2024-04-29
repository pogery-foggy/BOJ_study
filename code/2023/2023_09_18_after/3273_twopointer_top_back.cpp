#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;
int x, N, back, top, answer;
void init() {
    cin >> N;
    arr.resize(N);
    for (auto &a : arr) {
        cin >> a;
    }
    cin >> x;
    sort(arr.begin(), arr.end());
    back = 0;
    top = arr.size() - 1;
}

void solve() {
    while (back < top) {
        if (arr[back] + arr[top] == x) {
            answer++;
            top--;
            back++;
        } else if (arr[back] + arr[top] > x) {
            top--;
        } else
            back++;
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