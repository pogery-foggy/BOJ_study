#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define INF 2147483647

using namespace std;
bool answer[500001];
int N_user, N_card;
vector<int> arr_user, arr_card;
void init() {
    cin >> N_user;
    arr_user.resize(N_user);
    for (int i = 0; i < N_user; i++) {
        cin >> arr_user[i];
    }
    cin >> N_card;
    arr_card.resize(N_card);
    for (int i = 0; i < N_card; i++) {
        cin >> arr_card[i];
    }
    sort(arr_user.begin(), arr_user.end());
}

bool fnd(int x) {
    int l = 0;
    int h = N_user - 1;
    while (l <= h) {
        int mid = (l + h) >> 1;
        if (arr_user[mid] == x)
            return true;
        else if (x < arr_user[mid]) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return false;
}

void solve() {
    for (int i = 0; i < N_card; i++) {
        answer[i] = fnd(arr_card[i]);
        cout << answer[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}