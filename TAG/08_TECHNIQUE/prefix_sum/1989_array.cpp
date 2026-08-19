#include <iostream>
#include <stack>
#include <vector>
#define MAX_N 100002

using namespace std;

int N;
long long arr[MAX_N];
long long prefix_sum[MAX_N + 1];
int L[MAX_N], R[MAX_N]; // 왼쪽 오른쪽에서 나보다 작은 값
vector<int> st;
void init() {
    cin >> N;
    prefix_sum[0] = 0;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        prefix_sum[i] = prefix_sum[i - 1] + arr[i];
    }
}

long long solve() {
    st.reserve(N); // 미리 용량 확보해 두는 거. resize랑 다름
    st.clear();
    for (int i = 1; i <= N; i++) { // L
        while (!st.empty() && arr[st.back()] >= arr[i])
            st.pop_back();
        L[i] = (st.empty() ? 0 : st.back());
        st.push_back(i);
    }

    st.clear();
    for (int i = N; i > 0; i--) { // R
        while (!st.empty() && arr[st.back()] >= arr[i])
            st.pop_back();
        R[i] = (st.empty() ? N + 1 : st.back());
        st.push_back(i);
    }
    // 내보다 작은애들이 나오기전에 합을 더하고 곱하면 나와야 하는데

    long long ans = 0;
    long long maxl = 0, maxr = 0;
    for (int i = 1; i <= N; i++) {
        int l = L[i] + 1;
        int r = R[i] - 1;
        long long s = prefix_sum[r] - prefix_sum[l - 1];
        // cout << r << " " << l <<"\n";
        // cout << prefix_sum[r] << " " <<prefix_sum[l-1]<<"\n";
        // cout << arr[l] << " " << arr[i] << " " << arr[r] << " :" << s << "\n";
        if (ans <= s * arr[i]) {
            maxl = l;
            maxr = r;
            ans = s * arr[i];
        }
    }
    cout << ans << "\n" << maxl << " " << maxr;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}