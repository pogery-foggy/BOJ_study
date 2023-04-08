#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 5 - i; j < N; j++) {
            cout << " ";
        }
        for (int j = i; j < N; j++) {
            cout << "*";
        }
        cout << "\n";
    }

    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}