#include <iostream>

using namespace std;

int stack,N,a,total;
void init() {
    cin >> N;
    stack = 1;
}

void solve() {
    for(int i = 0; i<N; i++){
        cin >> a;
        if(a==1){
            total += stack;
            stack ++; 
        }
        else{
            stack = 1;
        }
    }
    cout << total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}