#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> arr;
int N, ago;
void init() {
    cin >> N;
    arr.resize(N);

    for (int i = 0; i < N; i++) {
        arr[i].resize(i + 1);
        for (auto &a : arr[i]) {
            cin >> a;
        }
    }
}

void solve() {
    // arr[i-1][j]+=max(arr[i][j],arr[i][j+1])

    for (int i = N - 1; i > 0; i--) {
        for (int j = 0; j < arr[i].size() - 1; j++){
            arr[i-1][j]+=max(arr[i][j],arr[i][j+1]);
        }
    }

    cout << arr[0][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}