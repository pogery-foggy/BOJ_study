#include <iostream>
#include <string>
using namespace std;

string s;
int answer,N;
void init() {
    cin >> N >> s;
}

void solve() {
    for(auto a : s){
        answer += a-'A'+1;
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