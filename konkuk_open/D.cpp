#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> arr;
stack<int> arr1, arr2;
int N, answer;

void init() {
    cin >> N;
    arr.resize(N);
    for (auto &a : arr) {
        cin >> a;
    }
    sort(arr.begin(), arr.end());
    arr1.push(arr[0]);
    arr2.push(-1);
}

void solve() {
    for (int i = 1; i < N; i++) {
        if (arr[i - 1] != arr[i])
            arr1.push(arr[i]);
        if (arr[i - 1] == arr[i]) {
            if (arr1.top() == arr[i])
                if (arr2.top() != arr[i])
                    arr2.push(arr[i]);
        }
    }
    cout << arr1.size() + arr2.size() -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}