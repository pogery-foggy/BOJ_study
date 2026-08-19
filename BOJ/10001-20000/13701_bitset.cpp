#include <iostream>
#include <bitset>
using namespace std;

bitset<1 << 25> arr;
int x;

void init() {}

void solve() {
    while(cin >> x){
        if(arr[x]) continue;
        arr.set(x);
        cout << x << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}