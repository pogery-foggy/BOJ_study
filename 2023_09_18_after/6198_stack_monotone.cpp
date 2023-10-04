#include <iostream>
#include <stack>
using namespace std;

stack<int> st;
int N, arr[80000], first;
long long answer;

void init() {
    answer = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    st.push(arr[0]);
    first = arr[0];
}

void solve() {
    for (int i = 1; i < N; i++) {

        // 모노톤 스택쌓기 시작
        if (st.top() > arr[i]) {
            st.push(arr[i]);
        }

        // 10, 10-3,+, 10-7, 10-7-4,+,10-7,+,10,+,12,12-4,+,12
        else {

            while ((!st.empty()) && (st.top() <= arr[i])) {
                st.pop();
                answer += st.size();
            }
            st.push(arr[i]);
        }
    }

    while ((!st.empty())) {
        st.pop();
        answer += st.size();
    }
    cout << answer;
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}
