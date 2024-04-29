#include <iostream>

using namespace std;
int N;
long long answer;
void init() { cin >> N; }

void solve() {
    for (int i = 1; i <= N; i++) {
        if (!(N % i))
            answer += i;
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}