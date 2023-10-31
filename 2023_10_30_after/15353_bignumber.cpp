#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

string A, B;
void init() {
    cin >> A >> B;
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
}

string sum(string num1, string num2) {
    string ret = "";
    int size = max(num1.size(), num2.size());
    int total = 0;

    for (int i = 0; i < size || total; i++) {
        if (num1.size() > i)
            total += num1[i] - '0';
        if (num2.size() > i)
            total += num2[i] - '0';
        ret += total % 10 + '0';
        total /= 10;
    }
    return ret;
}

void solve() {

    string answer = sum(A, B);

    for (int i = answer.size() - 1; i >= 0; i--)
        cout << answer[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();

    return 0;
}