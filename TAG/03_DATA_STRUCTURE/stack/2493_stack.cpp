#include <iostream>
#include <stack>
#define INF 2147000000
using namespace std;

stack<pair<int, int>> st;
int N;
int arr[500001];
int answer[500001];
void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    answer[0] = 0;
    st.push({INF, -1});
}

void solve() {
    for (int i = 0; i < N; i++) {
        while (arr[i] > st.top().first) {
            st.pop();
        }
        int cur = st.top().first;
        int idx = st.top().second;
        answer[i] = idx + 1;
        st.push({arr[i], i});
    }

    for (int i = 0; i < N; i++) {
        cout << answer[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}