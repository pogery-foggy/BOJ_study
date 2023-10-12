#include <iostream>

using namespace std;
int N, F, answer;
void init() { cin >> N >> F; }

void solve() {
    N -= N % 100;
    for (int i = 0; i < 100; i++) {
        if ((N + i) % F == 0) {
            answer = i;
            break;
        }
    }
    if(answer<10) cout << "0"<<answer;
    else cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}