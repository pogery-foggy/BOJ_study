#include <iostream>
#include <string>
using namespace std;

string s;
int arr[6] = {10, 11, 12, 13, 14, 15};
long long sum;
void init() { cin >> s; }

void solve() {
    for (auto a : s) {
        sum *= 16;
        if (a >= 'A' && a <= 'F') {
            sum += arr[a - 'A'];
        } else
            sum += a - '0';
    }
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}