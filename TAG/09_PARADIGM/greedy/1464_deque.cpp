#include <deque>
#include <iostream>
#include <string>
using namespace std;

string s;
deque<char> answer;
int a;

void init_() { cin >> s; }

void solve() {
    for (auto a : s) {
        if (answer.empty()) {
            answer.push_back(a);
            continue;
        }
        if (answer.back() >= a) {
            answer.push_back(a);
        } else {
            answer.push_front(a);
        }
    }
    while (!answer.empty()) {
        cout << answer.back();
        answer.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init_();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}