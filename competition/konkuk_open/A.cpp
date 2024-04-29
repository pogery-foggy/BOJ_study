#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> s;
int arr[1000];
int N, L, maxi, answer;
void init() {
    cin >> N >> L;
    s.resize(N);
    for (auto &a : s) {
        cin >> a;
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        int line = 0;
        if (s[i][0] == '1')
            line++;
        if (s[i][L - 1] == '1')
            line++;
        for (int j = 1; j < L; j++) {
            if (s[i][j] != s[i][j - 1])
                line++;
        }
        line /= 2;
        arr[i] = line;
        maxi = maxi > line ? maxi : line;
    }

    for (int i = 0; i < N; i++) {
        if (arr[i] == maxi)
            answer++;
    }

    cout << maxi << " " << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}