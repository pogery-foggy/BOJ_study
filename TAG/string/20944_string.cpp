#include <iostream>
#include <string>
using namespace std;
int N;
void init() {
    cin >> N;
}

void solve() {
    for(int i = 0 ; i < N ; i++){
        cout << 'a';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}