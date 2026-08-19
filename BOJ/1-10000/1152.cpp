#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string a;
    int cnt = 1;
    getline(cin, a);
    for (auto b : a) {
        if (b == ' ')
            cnt++;
    }
    if (a[0] == ' ')
        cnt--;
    if (a[a.size() - 1] == ' ')
        cnt--;
    cout << cnt;
}