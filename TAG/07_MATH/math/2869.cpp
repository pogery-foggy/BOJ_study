#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int A, B, V;
    cin >> A >> B >> V;
    int last = (V - A) / (A - B);
    if (!((V - A) % (A - B)))
        cout << last + 1;
    else
        cout << last + 2;
    return 0;
}