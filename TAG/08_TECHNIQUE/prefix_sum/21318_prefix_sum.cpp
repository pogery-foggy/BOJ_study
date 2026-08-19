#include <iostream>

using namespace std;
int arr[100001];
int prefix_sum[100001];
int N;
void init() {
    cin >> N;
    cin >> arr[1];
    for (int i = 2; i <= N; i++) {
        cin >> arr[i];
        if (arr[i - 1] > arr[i])
            prefix_sum[i - 1] = 1;
    }
    for (int i = 2; i <= N; i++) {
        prefix_sum[i] += prefix_sum[i - 1];
    }
}

void solve() {
    int Q;
    cin >> Q;
    while (Q--) {
        int s, e;
        cin >> s >> e;
        cout << prefix_sum[e - 1] - prefix_sum[s - 1] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}