#include <iostream>
#include <string>
#include <set>
using namespace std;

string s;
set<string> arr;

void init() {
    cin >> s;
}

void solve() {
    for(int i = 0; i < s.size(); i++){
        string temp = "";
        for(int j = i ; j <s.size(); j++){
            temp += s[j];
            arr.insert(temp);
        }
    }
    cout << arr.size();
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}