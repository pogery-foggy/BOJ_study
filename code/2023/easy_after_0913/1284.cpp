#include <iostream>
#include <string>
using namespace std;
int arr[10] = {4, 2, 3, 3, 3, 3, 3, 3, 3, 3}, total;
string s;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while (1) {
        total = 1;
        cin >> s;
        if (s == "0")
            break;
        for (auto a : s) {
            total += arr[a-'0'];
            total += 1;
        }
        cout << total << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}