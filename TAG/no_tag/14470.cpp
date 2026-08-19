#include <iostream>

using namespace std;
int a1, a2, u, d, e, t;
int main() {
    cin >> a1 >> a2 >> u >> d >> e;

    if (a1 < 0)
        t = -a1 * u + d + e * a2;
    else if (a1 == 0)
        t = d + e * a2;
    else
        t = e * (a2 - a1);

    cout << t << endl;
}