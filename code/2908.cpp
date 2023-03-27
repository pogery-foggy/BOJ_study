#include <iostream>
#include <string>
using namespace std;

string a, b;

bool comp(string t1, string t2) {
    for (int i = 2; i >= 0; i--) {
        if (t1[i] > t2[i])
            return true;
        else if (t1[i] < t2[i])
            return false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> a >> b;
    if (comp(a, b)) {
        for (int i = 2; i >= 0; i--) {
            cout << a[i];
        }
    } else {
        for (int i = 2; i >= 0; i--) {
            cout << b[i];
        }
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}