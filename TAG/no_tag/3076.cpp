#include <iostream>

using namespace std;
int R, C, A, B;
bool x = true, origin_x = true;
;
void init() { cin >> R >> C >> A >> B; }

void solve() {
    for (int i = 0; i < R; i++) {     // C개의 줄
        for (int j = 0; j < A; j++) { // 짤패 A
            x = origin_x;
            for (int k = 0; k < C; k++) { // k개의 칸
                for (int l = 0; l < B; l++) {
                    if (x)
                        cout << "X";
                    else
                        cout << ".";
                }
                x = !x;
            }
            cout << "\n";
        }
        origin_x = !origin_x;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}