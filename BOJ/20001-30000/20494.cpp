#include <iostream>
#include <string>
using namespace std;
string s;
int answer,N;
void init() {
    cin >> N;
}

void solve() {
    for(int i = 0 ; i <N; i++){
        cin >> s;
        answer += s.size();
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