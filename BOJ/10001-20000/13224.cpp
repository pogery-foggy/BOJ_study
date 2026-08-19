#include <iostream>
#include <string>
using namespace std;

bool cup[3] = {true,false,false};

string s;

void init() {
    cin >> s;
}

void solve() {
    for(auto a:s){
        if(a=='A'){
            bool tmp = cup[0];
            cup[0] = cup[1];
            cup[1] = tmp;
        }else if(a=='B'){
            bool tmp = cup[1];
            cup[1] = cup[2];
            cup[2] = tmp;
        }
        else{
            bool tmp = cup[0];
            cup[0] = cup[2];
            cup[2] = tmp;
        }
    }
    if(cup[0]) cout << 1;
    else if(cup[1]) cout << 2;
    else cout << 3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}