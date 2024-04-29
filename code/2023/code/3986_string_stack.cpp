#include <iostream>
#include <stack>
#include <string>
using namespace std;

string user_in;
stack<char> st;
int cnt;

void init() {
    cin >> user_in;
    while (!st.empty())
        st.pop();
    st.push(user_in[0]);
}

void solve() {
    for (int i = 1; i < user_in.size(); i++) {
        if (st.empty()) {
            st.push(user_in[i]);
            continue;
        }
        if (st.top() == user_in[i])
            st.pop();
        else
            st.push(user_in[i]);
    }
    if (st.empty())
        cnt++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    cout << cnt;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}