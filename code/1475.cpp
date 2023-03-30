#include <iostream>
#include <string>
using namespace std;

string N;
int arr[10], maxed = -1;
void init() { cin >> N; }

void solve() {

    for (auto a : N) {
        arr[a - '0']++;
    }
    arr[6] += arr[9] + 1;
    arr[6] /= 2;
    for (int i = 0; i < 9; i++) {
        maxed = maxed > arr[i] ? maxed : arr[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    cout << maxed << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}