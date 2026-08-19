#include <iostream>

using namespace std;

int N;
long long arr[200001], Q;
long long sum;
bool is_flow[200001];

void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        sum += arr[i];
        is_flow[i] = true;
    }
    cin >> Q;
}

void solve() {
    // first output
    cout << sum << "\n";

    for (int i = 0; i < Q; i++) {
        int query;
        cin >> query;
        switch (query) {
        int tab;
        case 1:
            long long change;
            cin >> tab >> change;
            if (is_flow[tab])
                sum += change - arr[tab];
            arr[tab] = change;
            break;
        case 2:
            cin >> tab;
            is_flow[tab] ^= true;
            if (is_flow[tab])
                sum += arr[tab];
            else
                sum -= arr[tab];
            break;
        }
        cout << sum << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}