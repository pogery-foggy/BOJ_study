#include <iostream>
#include <queue>
#include <string>
using namespace std;

deque<char> arr;
int N;
void init() {
    cin >> N;
    char a;
    cin >> a;
    arr.push_back(a);
}

void solve() {
    for (int i = 0; i < N - 1; i++) {
        char a;
        cin >> a;
        if (arr.front() >= a) {
            arr.push_front(a);
        } else
            arr.push_back(a);
    }

    while (!arr.empty()) {
        cout << arr.front();
        arr.pop_front();
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}