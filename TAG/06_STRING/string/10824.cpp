#include <iostream>
#include <string>
using namespace std;

string A,B,C,D;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> A >> B >> C >> D;
    A = A+B;
    C = C+D;
    cout << stoll(A) + stoll(C);
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}