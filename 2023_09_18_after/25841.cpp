#include <iostream>
#include <string>
using namespace std;

string s;
int l,r,cnt;
char fnd;
void init() {
    cin >> l >> r >> fnd;
}

void solve() {
    for(int i = l; i<=r; i++){
        s = to_string(i);
        for(auto a : s){
            if(a==fnd) cnt++;
        }
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}