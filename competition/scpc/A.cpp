#include <iostream>

using namespace std;

int answer = 0;
int arr[100001];
int five, ten, N;
void init() {
    five = 0;
    ten = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
}

int solve() {
    int i = 0;
    for (i = 0; i < N; i++) {
        if (arr[i] == 500)
            five++;
        else if (arr[i] == 1000) {
            if (five > 0) {
                five--;
                ten++;
            } else
                return i;
        } else {
            if (ten >= 4 && five >= 1) {
                ten -= 4;
                five -= 1;
            } else if (ten >= 3 && five >= 3) {
                ten -= 3;
                five -= 3;
            } else if (ten >= 2 && five >= 5) {
                ten -= 2;
                five -= 5;
            } else if (ten >= 1 && five >= 7) {
                ten -= 1;
                five -= 7;
            } else if (five >= 9) {
                five -= 9;
            } else
                return i;
        }
    }
    return i;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        answer = solve();
        cout << "Case #" << testcase + 1 << endl;
        cout << answer << endl;
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}