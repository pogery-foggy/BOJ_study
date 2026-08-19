#include <iostream>
#include <stack>
using namespace std;

int map[501];
stack<int> st;
int H, W;
int bigi;
int temp;
int answer = 0;

void init() {
    cin >> H >> W;
    for (int i = 0; i < W; i++)
        cin >> map[i];
    st.push(map[0]);
}
void solve() {
    
    cout << answer;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}