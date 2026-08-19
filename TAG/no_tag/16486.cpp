#include <iostream>
#define PI 3.141592
using namespace std;

double d1,d2;
void init() {cin >> d1 >> d2;}

void solve() {cout << fixed;
cout.precision(6);
cout << 2*d1 + 2*d2*PI;}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}