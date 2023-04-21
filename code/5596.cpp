#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N1, N2, N3, N4, S1, S2, S3, S4, totalN = 0, totalS = 0;
    cin >> N1 >> N2 >> N3 >> N4;
    cin >> S1 >> S2 >> S3 >> S4;
    totalN = N1 + N2 + N3 + N4;
    totalS = S1 + S2 + S3 + S4;
    cout << (totalN > totalS ? totalN : totalS);
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}