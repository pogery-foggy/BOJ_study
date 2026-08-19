#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> A;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int user_in;
    for (int i = 0; i < 3; i++) {
        cin >> user_in;
        A.push_back(user_in);
    }
    sort(A.begin(), A.end());
    cout << A[2] + A[1];
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}