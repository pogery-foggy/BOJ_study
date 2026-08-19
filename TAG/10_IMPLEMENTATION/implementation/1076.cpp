#include <cmath>
#include <iostream>
#include <string>
using namespace std;

string a, b, c;

int check(string s) {
    if (s == "black")
        return 0;
    else if (s == "brown")
        return 1;
    else if (s == "red")
        return 2;
    else if (s == "orange")
        return 3;
    else if (s == "yellow")
        return 4;
    else if (s == "green")
        return 5;
    else if (s == "blue")
        return 6;
    else if (s == "violet")
        return 7;
    else if (s == "grey")
        return 8;
    else if (s == "white")
        return 9;
}

void init() { cin >> a >> b >> c; }

void solve() {
    long long answer;
    answer = stoll(to_string(check(a)) + to_string(check(b)));
    long long po = ((long long)pow(10, check(c)) + 3);
    po -= po % 10;
    if (po == 0)
        po++;
    answer *= po;
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}