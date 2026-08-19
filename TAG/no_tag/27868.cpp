#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int N,point;
string s;
vector<char> arr;

void init() {
    cin >> N >> point;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
    }
    cin >> s;
    reverse(s.begin(),s.end());
}

void solve() {
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}