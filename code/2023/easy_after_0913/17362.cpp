#include <iostream>

using namespace std;
int N;
int arr[9] = {2,1,2,3,4,5,4,3};
void init() {
    cin >> N;
}

void solve() {
    cout << arr[N%8];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}