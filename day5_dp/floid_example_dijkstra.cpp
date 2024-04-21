#include <iostream>

using namespace std;

int D[100][100];
int n = 5;

int main() {
    // floyd
    for (int k = 1; k <= n; k++) { // 경유
        for (int i = 0; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j)
                    continue;
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << D[i][j];
        }
        cout << "\n";
    }

    return 0;
}
