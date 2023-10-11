#include <iostream>

using namespace std;
int cnt;
char arr[5] = {'E','A','B','C','D'};
void init() {
    cnt = 0;
}

void solve() {
    for(int i = 0 ; i <4 ;i++){
        int a;
        cin >> a;
        if(a == 0) cnt++;
    }
    cout << arr[cnt] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T=3;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}