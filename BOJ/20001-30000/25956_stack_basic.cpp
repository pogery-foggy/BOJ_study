#include <iostream>
#include <stack>
#include <utility>
using namespace std;
int sz = 1, cur;
int arr[1000001];
int answer[1000001];
stack<pair<int, int>> st;
int N;
bool flag;
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
}

void solve() {
    st.push({0, 0});
    for (int i = 1; i <= N; i++) {
        cur = arr[i];
        while (st.top().first >= cur)
            st.pop();
        if (st.top().first + 1 != cur) {
            flag = true;
            break;
        }
        answer[st.top().second]++;
        st.push({arr[i], i});
    }

    if (flag) {
        cout << -1;
        return;
    } else {
        for (int i = 1; i <= N; i++) {
            cout << answer[i] << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}