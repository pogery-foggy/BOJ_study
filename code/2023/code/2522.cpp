#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // N-1, N-2 N-3...N-N,N-N+1...N-1

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            cout << " ";
        }
        for (int j = N - i - 1; j < N; j++) {
            cout << "*";
        }
        cout << "\n";
    }

    for (int i = N - 2; i >= 0; i--) {
        for (int j = i + 1; j < N; j++) {
            cout << " ";
        }
        for (int j = N - i - 1; j < N; j++) {
            cout << "*";
        }
        cout << "\n";
    }

    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}