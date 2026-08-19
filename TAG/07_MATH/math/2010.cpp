#include <iostream>

using namespace std;

int total, a;
int N;
void init() {
    cin >> N;
    cin >> a;
    total += a;
    for(int i = 1;  i <N ; i++){
        cin >> a;
        total += a-1;
    }
}

void solve() {cout << total;}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}