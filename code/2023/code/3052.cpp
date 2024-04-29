#include <iostream>

using namespace std;

int dive[42];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int user_in;
    int cnt = 10;
    for (int i = 0; i < 10; i++) {
        cin >> user_in;
        int fnd = user_in % 42;
        if (dive[fnd])
            cnt--;
        dive[fnd]++;
    }

    cout << cnt << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}