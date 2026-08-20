#include <iostream>
#include <string>
using namespace std;
string N;
int B, answer;
void init() { cin >> N >> B; }

void solve() {
    for (int i = 0; i < N.size(); i++) {
        if (N[i] >= '0' && N[i] <= '9') {
            answer = answer * B + N[i] - '0';
        } else
            answer = answer * B + N[i] - 'A'+10;
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}