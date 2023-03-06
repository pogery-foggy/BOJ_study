#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string str;
    getline(cin, str);
    if (!str.compare("1 2 3 4 5 6 7 8"))
        cout << "ascending";
    else if (!str.compare("8 7 6 5 4 3 2 1"))
        cout << "descending";
    else
        cout << "mixed";
}