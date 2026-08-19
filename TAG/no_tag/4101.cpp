#include <iostream>
#include <string>
using namespace std;

int main() {
    int A, B;
    cin >> A >> B;
    while (A | B) {
        string answer;
        answer = A > B ? "Yes" : "No";
        cout << answer << "\n";
        cin >> A >> B;
    }
    return 0;
}