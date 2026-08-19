#include <iostream>

using namespace std;
int plag;
int N;
void init() { cin >> N; }

void print_star() {
    for (int i = 0; i < N * 2; i++) {
        if (i == N) {
            if (N % 2 == 1)
                cout << "\n";
            else
                cout<< "\n ";
        }
        if (i % 2 == 0)
            cout << "*";
        else
            cout << " ";
    }
}

void solve() {
    print_star();
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    for (int i = 0; i < N; i++)
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}