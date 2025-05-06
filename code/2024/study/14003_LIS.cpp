#include <algorithm>
#include <iostream>
#include <vector>
#define MAX_N 1000001
#define er -1000000001
using namespace std;

int arr[MAX_N], index[MAX_N], N, C[MAX_N], pre_index[MAX_N];

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        index[i] = i;
    }
    pre_index[0] = -1;
}

void solve() {
    vector<int> v;
    for (int i = 0; i < N; i++) {
        int a = arr[i];
        if (v.empty()) {
            v.push_back(a);
            index[0] = 0;
        }
        if (v.back() < a) {
            v.push_back(a);
            index[v.size() - 1] = i;
            pre_index[v.size() - 1] = index[v.size() - 2];
        } else {
            auto it = upper_bound(v.begin(), v.end(), a - 1);
            *it = a;
            int idx = it - v.begin();
            index[idx] = i;
            if (idx > 0)
                pre_index[idx] = index[idx - 1];
        }
    }
    cout << v.size() << "\n";
    vector<int> s;
    int cur = v.size() - 1;
    while (1) {
        if (pre_index[cur] == -1) {
            s.push_back(arr[index[cur]]);
            break;
        }
        s.push_back(arr[index[cur]]);
        cur = pre_index[cur];
    }
    for (int k = s.size() - 1; k >= 0; k--) {
        cout << s[k] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}