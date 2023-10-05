#include <iostream>
#include <string>
using namespace std;

string s;
int x, y, n;
void init() {
    cin >> s;
    cin >> n;
}

void swap(string &st){
    char temp = s[x];
    s[x] = s[y];
    s[y] = temp; 
}

void solve() {
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        swap(s);
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