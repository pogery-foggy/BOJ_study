#include <iostream>

using namespace std;

int b, posi, N, M, re_posi, query;

void init() {
    cin >> N >> posi >> M;
    re_posi = -(N - posi);
    posi -= 1;
    for (int i = 0; i < N; i++) {
        cin >> b;
    }
}

void solve() {
    for (int i = 0; i < M; i++) {
        cin >> query;
        if (query > 0) {
            if (query > posi) {
                posi = query - posi - 1;
                re_posi = -(N - posi) + 1;
            }
        } else {
            if (query < re_posi) {
                re_posi = -re_posi;
                re_posi = query + re_posi + 1;
                posi = N + re_posi - 1;
            }
        }
    }
    cout << posi + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}