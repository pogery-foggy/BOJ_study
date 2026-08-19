#include <deque>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string s, function, acp;
deque<int> ac;
int N;
bool front;

void init() {
    front = true;
    ac.clear();
    cin >> function;
    cin >> N;
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '[' || s.size() == 2)
            continue;
        else if (s[i] == ',' || s[i] == ']') {
            ac.push_back(stoi(acp));
            acp = "";
        } else {
            acp.push_back(s[i]);
        }
    }
}

void print_deque() {
    if (!ac.empty()) {
        if (front) {
            cout << "[";
            for (int i = 0; i < ac.size() - 1; i++) {
                cout << ac[i] << ",";
            }
            cout << ac[ac.size() - 1] << "]\n";
        } else {
            cout << "[";
            for (int i = ac.size() - 1; i > 0; i--) {
                cout << ac[i] << ",";
            }
            cout << ac[0] << "]\n";
        }
    } else if (ac.size() == 0) {
        cout << "[]\n";
    } else
        cout << "error\n";
}

void solve() {
    for (auto func : function) {
        if (func == 'R')
            front = !front;
        else {
            if (ac.empty()) {
                cout << "error\n";
                return;
            } else {
                if (front)
                    ac.pop_front();
                else
                    ac.pop_back();
            }
        }
    }
    print_deque();
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