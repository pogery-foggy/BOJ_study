#include <iostream>
#include <stack>
using namespace std;

stack<int> st;
int arr[1000001];
int nge[1000001];
int N;

void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
}

void solve() {
    for (int i = N; i > 0; i--) {

        while (!st.empty() && st.top() <= arr[i])
            st.pop();

        if (st.empty())
            nge[i] = -1;
        else
            nge[i] = st.top();

        st.push(arr[i]);
    }
    for (int i = 1; i <= N; i++) {
        cout << nge[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}