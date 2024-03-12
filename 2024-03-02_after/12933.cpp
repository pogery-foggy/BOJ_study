#include <iostream>
#include <string>
using namespace std;

string s;
int maxi = -1, st;
int arr[5];
// quack
int alpha[26] = {2, -1, 3, -1, -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, 0, -1, -1, -1, 1, -1, -1, -1, -1, -1};

void init() { cin >> s; }

int solve() {
    for (auto a : s) {
        int cur = alpha[a - 'a'];
        if (cur == -1)
            return -1;
        else if (cur == 0) {
            st++;
            arr[cur]++;
        } else if (cur == 4) {
            maxi = st > maxi ? st : maxi;
            st--;
        }
        if (cur > 0) {
            arr[cur]++;
            if (arr[cur] > arr[cur - 1])
                return -1;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (arr[i] != arr[i + 1])
            return -1;
    }
    return maxi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    cout << solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}