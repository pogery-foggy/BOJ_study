#include <iostream>

using namespace std;
int pow(int a) { return a * a; }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, total = 0;

    for (int i = 0; i < 5; i++) {
        cin >> N;
        total += pow(N);
    }
    cout << total % 10;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}