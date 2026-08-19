#include <iostream>
#include <stack>
#include <string>
using namespace std;

string s;
void init() { getline(cin, s); }

void solve() {
    stack<char> st;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '<') {
            if (!st.empty()) {
                while (!st.empty()) {
                    char cur = st.top();
                    cout << cur;
                    st.pop();
                }
            }
            cout << "<";
            while (s[++i] != '>') {
                cout << s[i];
            }
            cout << ">";
        } else if (s[i] == ' ') {
            while (!st.empty()) {
                char cur = st.top();
                cout << cur;
                st.pop();
            }
            cout << " ";
        } else
            st.push(s[i]);
    }
    while (!st.empty()) {
        char cur = st.top();
        cout << cur;
        st.pop();
    }
    cout << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}