#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
int K, D, A;
string stringBuffer;
vector<string> x;
string s;
void init() {
    cin >> s;

    istringstream ss(s);
    while (getline(ss, stringBuffer, '/')) {
        x.push_back(stringBuffer);
    }
    K = stoi(x[0]);
    D = stoi(x[1]);
    A = stoi(x[2]);
}

void solve() {
    if (K + A < D || D == 0)
        cout << "hasu";
    else
        cout << "gosu";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}