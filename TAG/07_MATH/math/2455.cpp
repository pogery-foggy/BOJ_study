#include <iostream>

using namespace std;
int x, y,maxi = -1,total;
void init() {}

void solve() {
    while (1) {
        cin >> x >> y;
        if (y == 0)
            break;
        
        total += y-x; 
        maxi = maxi>total?maxi:total;
    }
    cout << maxi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}