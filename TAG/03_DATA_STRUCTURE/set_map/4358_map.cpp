#include <iostream>
#include <map>
using namespace std;

map<string, double> m;
double total;
string s;

void init() {
    while (getline(cin, s)) {
        m[s]++;
        total++;
    }
    for (auto a : m) {
        cout << a.first << " ";
        cout << fixed;
        cout.precision(4);
        cout << a.second / total * 100 << "\n";
    }
}

void solve() {}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}