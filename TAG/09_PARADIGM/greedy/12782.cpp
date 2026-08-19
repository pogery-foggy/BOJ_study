#include <iostream>
#include <string>
using namespace std;

string a, b;
int wrong[2];
void init() {
    cin >> a >> b;
    wrong[0] = wrong[1] = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            wrong[a[i] - '0']++;
        }
    }
}

void solve() {
    //cout << wrong[0] << " " << wrong[1];
    if (wrong[0] < wrong[1]) {
        int temp = wrong[0];
        wrong[0] = wrong[1];
        wrong[1] = temp;
    }
    cout << wrong[0]<<"\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}