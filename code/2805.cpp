#include <iostream>

using namespace std;

long long N, M, stack;
int arr[1000000], l, r, max_tree = -1, answer;

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        max_tree = max_tree > arr[i] ? max_tree : arr[i];
    }
    l = 1;
    r = max_tree;
}

void solve() {
    long long mid;
    while (l <= r) {
        stack = 0;
        mid = (l + r) >> 1;
        for (int i = 0; i < N; i++) {
            if (arr[i] > mid) {
                stack += arr[i] - mid;
            }
        }
        if (stack >= M) {
            answer = mid;
            l = mid + 1;
        } else
            r = mid - 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << answer;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}