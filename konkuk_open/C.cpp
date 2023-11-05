#include <iostream>
#include <string>
using namespace std;

int N, L;
string s;

void init() {
    cin >> N >> L;
    if(N == 0){
        s += "10";
    }
    else{
        s.push_back(N+'0');
        s.push_back('1');
    }
}

void solve() {
    for(int i = 0 ; i < L-2; i++){
        s.push_back('1');
    }
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}