#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> arr;

void init() {
    cin >> N;
    arr.clear();
}

void solve() {
    int sum = 0;
    for (int i = 1; i <= N / 2; i++) {
        if (N % i == 0) {
            arr.push_back(i);
            sum += i;
        }
    }
    if (sum == N) {
        cout << N << " = ";
        for (int i = 0; i < arr.size() - 1; i++) {
            cout << arr[i] << " + ";
        }
        cout << arr[arr.size() - 1] << "\n";
    } else {
        cout << N << " is NOT perfect.\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    while (N != -1) {
        solve();
        init();
    }

    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}