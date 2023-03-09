#include <iostream>

using namespace std;
int answer, ans2, ans3, N;
void init() { cin >> N; }

void solve() {
    answer = N / 5;
    ans2 = N / 25;
    ans3 = N / 125;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    solve();
    cout << answer + ans2 + ans3;
    return 0;
}