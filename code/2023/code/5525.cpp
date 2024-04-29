#include <iostream>
#include <string>
using namespace std;
int N, M, answer, correct;
string S;
void init() {
    cin >> N >> M;
    cin >> S;
}

void solve() {
    for (int i = 0; i < M; i++) {
        if (S[i] == 'I') {
            correct = 0;
            while (S[i + 1] == 'O' && S[i + 2] == 'I') {
                correct++;
                i += 2;
                if (correct == N) {
                    answer++;
                    correct--;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();
    solve();
    cout << answer;

    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}