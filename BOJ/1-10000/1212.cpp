#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string bin[8] = {"000", "001", "010", "011", "100", "101", "110", "111"};
    string bin_first[8] = {"", "1", "10", "11", "100", "101", "110", "111"};
    string user_in;
    cin >> user_in;
    if (user_in == "0")
        cout << 0;
    cout << bin_first[user_in[0] - '0'];
    for (int i = 1; i < user_in.size(); i++) {
        cout << bin[user_in[i] - '0'];
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}