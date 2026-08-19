#include <iostream>
#include <string>
using namespace std;

int N, answer;
int arr[4]; // N S E W
string S;
void init() { cin >> N >> S; }

void solve() {
    for (auto a : S) {
        if (a == 'N')
            arr[0]++;
        else if (a == 'S')
            arr[1]++;
        else if (a == 'E')
            arr[2]++;
        else
            arr[3]++;
    }
    answer += arr[0] - arr[1] > 0 ? arr[0] - arr[1] : arr[1] - arr[0];
    answer += arr[2] - arr[3] > 0 ? arr[2] - arr[3] : arr[3] - arr[2];
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