#include <iostream>

using namespace std;

long long man, time;

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        cin >> man >> time;
        cout << man + (time / 4) - (time / 7) << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}