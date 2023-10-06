#include <iostream>
#include <string>
using namespace std;

string s, answer;
int cnt;
void init() { cin >> s; }

void solve() {
    if(s == "P"){
        cout << "PPAP";
        return;
    }
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == 'P') {
            answer.push_back('P');
            cnt++;
        } else {
            if ((cnt >= 2) && (s[i + 1] == 'P')) {
                answer.pop_back();
                answer.pop_back();
                cnt -= 2;
            } else {
                cout << "NP";
                return;
            }
        }
    }
    if (answer.empty() && s[s.size()-1] !='A')
        cout << "PPAP";
    else
        cout << "NP";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}