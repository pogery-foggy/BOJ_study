#include <iostream>
#include <string>

using namespace std;

int main(void) {

    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    int N;
    char B;
    cin >> N >> B;

    int result = 0;
    for (int i = 0; i < 4 * N; i++) {
        string temp;
        cin >> temp;
        switch (temp[0]) {
        case 'A':
            result += 11;
            break;
        case 'K':
            result += 4;
            break;
        case 'Q':
            result += 3;
            break;
        case 'J':
            if (temp[1] == B)
                result += 20;
            else
                result += 2;
            break;
        case 'T':
            result += 10;
            break;
        case '9':
            if (temp[1] == B)
                result += 14;
            break;
        case '8':
            break;
        case '7':
            break;
        }
    }
    cout << result << "\n";

    return 0;
}