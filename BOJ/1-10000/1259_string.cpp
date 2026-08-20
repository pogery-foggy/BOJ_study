#include <iostream>
#include <string>
using namespace std;

string user_in, answer;
int arr_size;

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    while (1) {
        cin >> user_in;
        if (user_in == "0")
            break;
        arr_size = user_in.size();
        answer = "yes";
        for (int i = 0; i < arr_size; i++) {
            if (user_in[i] != user_in[arr_size - i - 1])
                answer = "no";
        }
        cout << answer << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}