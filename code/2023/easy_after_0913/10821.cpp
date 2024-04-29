#include <iostream>
#include <string>
using namespace std;
string s;
void init() {cin >> s;}

void solve() {
    int answer = 1;
    for(auto a : s){
        if(a == ',') answer++;
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}